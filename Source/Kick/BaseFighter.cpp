// Fill out your copyright notice in the Description page of Project Settings.

#include "Kick.h"
#include "BaseFighter.h"
#include "FighterMovementComponent.h"

FName ABaseFighter::MovementComponentName(TEXT("MovementComponent0"));
FName ABaseFighter::CollisionComponentName(TEXT("CollisionComponent0"));
FName ABaseFighter::MeshComponentName(TEXT("MeshComponent0"));

ABaseFighter::ABaseFighter(const FObjectInitializer& ObjectInitializer) {
    
    // Initializing class variables.
    PrimaryActorTick.bCanEverTick = true;
    bCollideWhenPlacing = false;
    JiggleDuration = 0.0f;

    CollisionComponent = ObjectInitializer.CreateDefaultSubobject<UBoxComponent>(this, ABaseFighter::CollisionComponentName);
    CollisionComponent->SetCollisionProfileName(TEXT("Pawn"));
    CollisionComponent->CanCharacterStepUpOn = ECB_No;
    CollisionComponent->bShouldUpdatePhysicsVolume = true;
    CollisionComponent->bCanEverAffectNavigation = false;
    
    // Setting the collision component to be the root component.
    RootComponent = CollisionComponent;
    
    MovementComponent = ObjectInitializer.CreateDefaultSubobject<UFighterMovementComponent>(this, ABaseFighter::MovementComponentName);
    MovementComponent->UpdatedComponent = CollisionComponent;
    
    MeshComponent = ObjectInitializer.CreateOptionalDefaultSubobject<USkeletalMeshComponent>(this, ABaseFighter::MeshComponentName);
    if (MeshComponent) {
        MeshComponent->AlwaysLoadOnClient = true;
        MeshComponent->AlwaysLoadOnServer = true;
        MeshComponent->bOwnerNoSee = false;
        MeshComponent->PrimaryComponentTick.TickGroup = TG_PrePhysics;
        MeshComponent->AttachParent = RootComponent;
        MeshComponent->bGenerateOverlapEvents = false;
        MeshComponent->bCanEverAffectNavigation = false;
        MeshComponent->MeshComponentUpdateFlag = EMeshComponentUpdateFlag::AlwaysTickPose;
        MeshComponent->bCastDynamicShadow = true;
        MeshComponent->bAffectDynamicIndirectLighting = true;
    }
}

void ABaseFighter::Tick(float DeltaSeconds) {
    Super::Tick(DeltaSeconds);
    
    // Handling jiggle of the mesh component.
    FVector Location = MeshComponent->GetRelativeTransform().GetLocation();
    if (JiggleDuration > 0.0f) {
        JiggleDuration -= DeltaSeconds;
        float Switch = (sin(GetWorld()->TimeSeconds * 60.0f) + 1.0f) * 0.5f;
        float Sign = FGenericPlatformMath::RoundToFloat(Switch) > 0 ? 1.0f : -1.0f;
        MeshComponent->SetRelativeLocation(FVector(2.5f * Sign, Location.Y, Location.Z));
    } else {
        JiggleDuration = 0.0f;
        MeshComponent->SetRelativeLocation(FVector(0.0f, Location.Y, Location.Z));
    }
}

void ABaseFighter::PostInitializeComponents()
{
    Super::PostInitializeComponents();
    
    if (!IsPendingKill()) {
        if (MeshComponent) {
            // Force animation tick after movement component updates.
            if (MeshComponent->PrimaryComponentTick.bCanEverTick && MovementComponent) {
                MeshComponent->PrimaryComponentTick.AddPrerequisite(MovementComponent, MovementComponent->PrimaryComponentTick);
            }
        }
    }
}

UBoxComponent* ABaseFighter::GetCollisionComponent() const {
    return CollisionComponent;
}

USkeletalMeshComponent* ABaseFighter::GetMeshComponent() const {
    return MeshComponent;
}

UPawnMovementComponent* ABaseFighter::GetMovementComponent() const
{
    return MovementComponent;
}

void ABaseFighter::Jiggle(float Duration) {
    JiggleDuration = Duration;
}


