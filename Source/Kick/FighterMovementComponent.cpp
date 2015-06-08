// Fill out your copyright notice in the Description page of Project Settings.

#include "Kick.h"
#include "BaseFighter.h"
#include "FighterMovementComponent.h"

const float UFighterMovementComponent::MIN_FLOOR_DIST = 1.9f;

UFighterMovementComponent::UFighterMovementComponent(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer) {
    bAutoRegisterUpdatedComponent = true;
    bPositionCorrected = false;
    bGrounded = false;
    bHasDestination = false;
    Destination = FVector::ZeroVector;
    ResetMoveState();
}

void UFighterMovementComponent::SetVelocity(FVector NewVelocity) {
    Velocity = NewVelocity;
}

bool UFighterMovementComponent::IsMovingOnGround() const {
    return bGrounded;
}

void UFighterMovementComponent::SetDestination(FVector NewDestination) {
	Destination = NewDestination;
    bHasDestination = true;
}

void UFighterMovementComponent::AddImpulse(FVector AddedImpulse) {
    AddInputVector(AddedImpulse, true);
}

void UFighterMovementComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) {
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    if (!PawnOwner || !UpdatedComponent || ShouldSkipUpdate(DeltaTime)) {
        return;
    }
    
    // Location fixed to be at the bottom of the collision component.
    FVector Offset = FVector(0.0f, 0.0f, Cast<UBoxComponent>(UpdatedComponent)->GetUnscaledBoxExtent().Z);
    FVector Location = UpdatedComponent->GetComponentLocation() - Offset;

    // Figuring if the fighter is grounded.
    if (Location.Z >= MIN_FLOOR_DIST) {
        if (bGrounded) {
            Cast<ABaseFighter>(PawnOwner)->Jumped();
        }
        bGrounded = false;
    } 

    else if (Location.Z < MIN_FLOOR_DIST) {
        if (!bGrounded) {
            Cast<ABaseFighter>(PawnOwner)->Landed();
        }
        bGrounded = true;
    }

    const AController* Controller = PawnOwner->GetController();
    if (Controller && Controller->IsLocalController()) {
        if (Controller->IsLocalPlayerController()) {
            
            // Calculating velocity to destination.
            if (bHasDestination) {
                FVector Travel = Destination - Location;
                if (!Travel.IsNearlyZero(2.0f)) {
                    Velocity.Y = Travel.GetSafeNormal().Y * 1000.0f;
                } else {
                    Velocity.Y = 0.0f;
                    bHasDestination = false;
                    Location.Y = Destination.Y;
                    GetOwner()->SetActorLocation(Location, true);
                }
            }

			// Applying forces to velocity.
			Velocity += GetPendingInputVector();
			Velocity.Z += GetGravityZ() * 0.05f;
			ConsumeInputVector();
        }

        LimitWorldBounds();
        bPositionCorrected = false;

        // Getting the delta velocity.
        FVector Delta = Velocity * DeltaTime;

        if (!Delta.IsNearlyZero(1e-6f)) {
            const FRotator Rotation = UpdatedComponent->GetComponentRotation();

            FHitResult Hit(1.f);
            SafeMoveUpdatedComponent(Delta, Rotation, true, Hit);

            if (Hit.IsValidBlockingHit()) {
                HandleImpact(Hit, DeltaTime, Delta);
                SlideAlongSurface(Delta, 1.f-Hit.Time, Hit.Normal, Hit, true);
            }
        }
        
        // Finalizing.
        UpdateComponentVelocity();
    }
}

bool UFighterMovementComponent::ResolvePenetrationImpl(const FVector& Adjustment, const FHitResult& Hit, const FQuat& NewRotationQuat) {
    bPositionCorrected |= Super::ResolvePenetrationImpl(Adjustment, Hit, NewRotationQuat);
    return bPositionCorrected;
}

bool UFighterMovementComponent::LimitWorldBounds() {
    AWorldSettings* WorldSettings = PawnOwner ? PawnOwner->GetWorldSettings() : NULL;
    if (!WorldSettings || !WorldSettings->bEnableWorldBoundsChecks || !UpdatedComponent) {
        return false;
    }
    
    const FVector CurrentLocation = UpdatedComponent->GetComponentLocation();
    if ( CurrentLocation.Z < WorldSettings->KillZ ) {
        Velocity.Z = FMath::Min(GetMaxSpeed(), WorldSettings->KillZ - CurrentLocation.Z + 2.0f);
        return true;
    }
    
    return false;
}

