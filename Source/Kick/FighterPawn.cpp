// Fill out your copyright notice in the Description page of Project Settings.

#include "Kick.h"
#include "FighterPawn.h"
#include "FighterMovementComponent.h"
#include "FighterSkeletalMeshComponent.h"

FName AFighterPawn::MovementComponentName(TEXT("MovementComponent0"));
FName AFighterPawn::CollisionComponentName(TEXT("CollisionComponent0"));
FName AFighterPawn::MeshComponentName(TEXT("MeshComponent0"));

AFighterPawn::AFighterPawn(const FObjectInitializer& ObjectInitializer) {
    
    // Initializing class variables.
    Grounded = false;
    PrimaryActorTick.bCanEverTick = true;
    bCollideWhenPlacing = false;
    JiggleDuration = 0.0f;

    CollisionComponent = ObjectInitializer.CreateDefaultSubobject<UBoxComponent>(this, AFighterPawn::CollisionComponentName);
    CollisionComponent->SetCollisionProfileName(TEXT("Pawn"));
    CollisionComponent->CanCharacterStepUpOn = ECB_No;
    CollisionComponent->bShouldUpdatePhysicsVolume = true;
    CollisionComponent->bCanEverAffectNavigation = false;
    
    // Setting the collision component to be the root component.
    RootComponent = CollisionComponent;
    
    MovementComponent = ObjectInitializer.CreateDefaultSubobject<UFighterMovementComponent>(this, AFighterPawn::MovementComponentName);
    MovementComponent->UpdatedComponent = CollisionComponent;
    
    MeshComponent = ObjectInitializer.CreateOptionalDefaultSubobject<UFighterSkeletalMeshComponent>(this, AFighterPawn::MeshComponentName);
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

void AFighterPawn::Tick(float DeltaSeconds) {
    Super::Tick(DeltaSeconds);
    
    // Emit the landing event.
    if (MovementComponent->Grounded & (MovementComponent->Grounded != Grounded)) {
        Landed();
    }
    Grounded = MovementComponent->Grounded;
    
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

void AFighterPawn::PostInitializeComponents()
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

void AFighterPawn::Jiggle(float Duration) {
    JiggleDuration = Duration;
}

float AFighterPawn::PlayAnimMontage(class UAnimMontage* AnimMontage, float InPlayRate, FName StartSectionName)
{
    UAnimInstance * AnimInstance = (MeshComponent)? MeshComponent->GetAnimInstance() : NULL; 
    if( AnimMontage && AnimInstance )
    {
        float const Duration = AnimInstance->Montage_Play(AnimMontage, InPlayRate);

        if (Duration > 0.f)
        {
            // Start at a given Section.
            if( StartSectionName != NAME_None )
            {
                AnimInstance->Montage_JumpToSection(StartSectionName, AnimMontage);
            }

            return Duration;
        }
    }   

    return 0.f;
}

void AFighterPawn::StopAnimMontage(class UAnimMontage* AnimMontage)
{
    UAnimInstance * AnimInstance = (MeshComponent)? MeshComponent->GetAnimInstance() : NULL; 
    UAnimMontage * MontageToStop = (AnimMontage)? AnimMontage : GetCurrentMontage();
    bool bShouldStopMontage =  AnimInstance && MontageToStop && !AnimInstance->Montage_GetIsStopped(MontageToStop);

    if ( bShouldStopMontage )
    {
        AnimInstance->Montage_Stop(MontageToStop->BlendOutTime, MontageToStop);
    }
}

class UAnimMontage * AFighterPawn::GetCurrentMontage()
{
    UAnimInstance * AnimInstance = (MeshComponent)? MeshComponent->GetAnimInstance() : NULL; 
    if ( AnimInstance )
    {
        return AnimInstance->GetCurrentActiveMontage();
    }

    return NULL;
}


