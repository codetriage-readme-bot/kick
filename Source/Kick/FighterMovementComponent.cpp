// Fill out your copyright notice in the Description page of Project Settings.

#include "Kick.h"
#include "BaseFighter.h"
#include "FighterMovementComponent.h"

// TODO: This value is relatively arbitrary.
const float UFighterMovementComponent::MIN_FLOOR_DIST = 1.9f;

UFighterMovementComponent::UFighterMovementComponent(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer) {
    bAutoRegisterUpdatedComponent = true;
    bPositionCorrected = false;
    bFrozen = false;
    bHasDestination = false;
    Cruise = FVector::ZeroVector;
    
    // TODO: This friction values is arbitrary.
    Friction = 10.0f;
    Destination = FVector::ZeroVector;
    ResetMoveState();
}

void UFighterMovementComponent::SetVelocity(FVector NewVelocity) {
    Cruise = NewVelocity;
    Velocity = NewVelocity;
}

void UFighterMovementComponent::SetFrozen(bool NewFrozen) {
    bFrozen = NewFrozen;
}

void UFighterMovementComponent::SetFriction(float NewFriction) {
    Friction = NewFriction;
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
    
    // If frozen we stop processing movement.
    if (!PawnOwner || !UpdatedComponent || ShouldSkipUpdate(DeltaTime) || bFrozen) {
        return;
    }
    
    // Location fixed to be at the bottom of the collision component.
    FVector Offset = FVector(0.0f, 0.0f, Cast<UBoxComponent>(UpdatedComponent)->GetUnscaledBoxExtent().Z);
    FVector Location = UpdatedComponent->GetComponentLocation() - Offset;
    
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

    // Applying impulsions.
    Velocity += GetPendingInputVector();
    ConsumeInputVector();
    
    // Applying fake friction.
    Velocity.X = Velocity.X > 0.0f ? FGenericPlatformMath::Max(Velocity.X * (1 - DeltaTime * Friction), Cruise.X): FGenericPlatformMath::Min(Velocity.X * (1 - DeltaTime * Friction), Cruise.X);
    
    // Applying gravity.
    Velocity.Z += GetGravityZ() * DeltaTime;

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

