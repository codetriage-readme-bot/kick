// Fill out your copyright notice in the Description page of Project Settings.

#include "Kick.h"
#include "CustomSkeletalMeshComponent.h"

UCustomSkeletalMeshComponent::UCustomSkeletalMeshComponent(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
    LastAnimationUpdate = 0.0f;
}

void UCustomSkeletalMeshComponent::TickPose(float DeltaTime, bool bNeedsValidRootMotion)
{
    
    // Updating the last animation update time.
    LastAnimationUpdate += DeltaTime;
    
    // If the last animation update did not reach the animation update frequency we skip.
    if (LastAnimationUpdate < AnimationUpdateFrequency) {
        return;
    }
    
    // Updating.
    Super::TickPose(LastAnimationUpdate, bNeedsValidRootMotion);
    
    // Resetting the last animation update value since we are updating.
    LastAnimationUpdate = 0.0f;
}
