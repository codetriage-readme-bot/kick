// Fill out your copyright notice in the Description page of Project Settings.

#include "Kick.h"
#include "FighterMovementComponent.h"

UFighterMovementComponent::UFighterMovementComponent(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer) {
    Impulse = FVector::ZeroVector;
    Drag = 0.0f;
    Grounded = false;
    Frozen = false;
    TargetDepth = 0.0f;
    Recursions = 0;
    GravityInfluence=1.0f;
}

void UFighterMovementComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) {
    
    // Calling super method.
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    
    // If frozen we stop processing movement.
    if (!UpdatedComponent->GetOwner() || !UpdatedComponent || ShouldSkipUpdate(DeltaTime) || Frozen) {
        return;
    }
    
    Recursions = 0;
    FVector Delta = Velocity * DeltaTime;
    Move(Delta);
    UpdateVelocity(DeltaTime);
}

void UFighterMovementComponent::Move(FVector Delta) {
    
    // Since the collision fixing is recursive. This will guarantee that we endup bailing out.
    Recursions += 1;
    if (Recursions >= 10) {
        return;
    }
    
    FHitResult Hit(1.f);
    SafeMoveUpdatedComponent(Delta, FRotator::ZeroRotator, true, Hit);
    
    // Recursively looping until we fix all collisions.
    if (Hit.IsValidBlockingHit()) {
        
        // Handling the collision.
        UBoxComponent* OtherComponent = (UBoxComponent*)Hit.Component.Get();
        FName OtherProfile = OtherComponent->GetCollisionProfileName();
        
        // If we are hitting the ground, we reset the vertical velocity.
        if (OtherProfile == FName("Ground")) {
            Delta = FVector::VectorPlaneProject(Delta, Hit.Normal);
            Velocity.Z = 0.0f;
            Grounded = true;
            Move(Delta);
            return;
        }
        
        // Otherwise we might be hitting a wall.
        if (OtherProfile == FName("Obstacle")) {
            
            // We will simply slide against it.
            Delta = FVector::VectorPlaneProject(Delta, Hit.Normal);
            Move(Delta);
            return;
        }
            
        // If are hitting the opponent from above or from the side. We fix the position.
        if (IsAbove(OtherComponent) || IsFlanking(OtherComponent)) {
            
            // We fix its location to fall on either side of the other actor.
            Move(FVector(GetHorizontalOverlap(OtherComponent), 0.0f, 0.0f));
            return;
        }
        
        // Otherwise we are simply flanking the opponent and we will slide against him.
        if (!Grounded) {
            Delta = FVector::VectorPlaneProject(Delta, Hit.Normal);
            Move(Delta);
            return;
        }
        
        // Otherwise we will push him.
        Delta = Hit.Normal * FVector::DotProduct(Delta, Hit.Normal) * 0.5;
        UFighterMovementComponent* OtherMovement = (UFighterMovementComponent*)Hit.Actor->GetComponentByClass(GetClass());
        OtherMovement->MoveUpdatedComponent(Delta, FQuat::Identity, true);
        Move(Delta);
        return;
    }
}

void UFighterMovementComponent::UpdateVelocity(float DeltaTime) {
    
    Velocity += Impulse;
    Impulse = FVector::ZeroVector;
    
    // Updating horizontal velocity.
    Velocity.X = Velocity.X * (1 - Drag * DeltaTime);

    // Updating vertical velocity.
    Velocity.Z += GetGravityZ() * GravityInfluence * DeltaTime;

    // I think this is the best moment to do this.
    if (Velocity.Z > 0) {
        Grounded = false;
    }
    
    // Updating deep velocity.
    FVector Location = UpdatedComponent->GetComponentLocation();
    float DepthTravel = TargetDepth - Location.Y;
    if (FGenericPlatformMath::Abs(DepthTravel) > 10.0f) {
        Velocity.Y = DepthTravel >= 0 ? 1000.0f : -1000.0f;
    } else {
        Velocity.Y = 0.0f;
        Location.Y = TargetDepth;
        UpdatedComponent->SetWorldLocation(Location);
    }
}

void UFighterMovementComponent::AddImpulse(FVector NewImpulse) {
    Impulse += NewImpulse;
}

bool UFighterMovementComponent::IsAbove(UBoxComponent* OtherComponent) {
    float Bottom = UpdatedComponent->GetComponentLocation().Z - ((UBoxComponent*)UpdatedComponent)->GetScaledBoxExtent().Z;
    float OtherTop = OtherComponent->GetComponentLocation().Z + OtherComponent->GetScaledBoxExtent().Z;
    return Bottom >= OtherTop;
}

bool UFighterMovementComponent::IsFlanking(UBoxComponent* OtherComponent) {
	float Extent = ((UBoxComponent*)UpdatedComponent)->GetScaledBoxExtent().Y;
	float OtherExtent = OtherComponent->GetScaledBoxExtent().Y;

	float Depth = UpdatedComponent->GetComponentLocation().Y;
	float OtherDepth = OtherComponent->GetComponentLocation().Y;

	float Closest = Depth + Extent;
	float OtherClosest = OtherDepth + OtherExtent;
	
	float Furthest = Depth - Extent;
	float OtherFurthest = OtherDepth - OtherExtent;

	return (Depth != TargetDepth) && ((Closest >= OtherFurthest) || (Furthest <= OtherClosest));
}

float UFighterMovementComponent::GetHorizontalOverlap(UBoxComponent* OtherComponent) {
    float Location = UpdatedComponent->GetComponentLocation().X;
    float OtherLocation = OtherComponent->GetComponentLocation().X;
    UBoxComponent* BoxComponent = (UBoxComponent*)UpdatedComponent;
    
    // If the other actor is on our left.
    if (Location > OtherLocation) {
        
        // We basically calculate how horizontal overlap our actor has with the other one.
        float Left = UpdatedComponent->GetComponentLocation().X - BoxComponent->GetScaledBoxExtent().X;
        float OtherRight = OtherComponent->GetComponentLocation().X + OtherComponent->GetScaledBoxExtent().X;
        return OtherRight - Left + 1.0f;
        
        // If the other actor in our right.
    } else {
        
        // We basically calculate how horizontal overlap our actor has with the other one.
        float Right = UpdatedComponent->GetComponentLocation().X + BoxComponent->GetScaledBoxExtent().X;
        float OtherLeft = OtherComponent->GetComponentLocation().X - OtherComponent->GetScaledBoxExtent().X;
        return OtherLeft - Right - 1.0f;
    }
}

