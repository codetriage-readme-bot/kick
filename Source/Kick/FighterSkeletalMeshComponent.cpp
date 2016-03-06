// Fill out your copyright notice in the Description page of Project Settings.

#include "Kick.h"
#include "FighterSkeletalMeshComponent.h"

UFighterSkeletalMeshComponent::UFighterSkeletalMeshComponent(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
    LastPoseUpdate = 0.0f;
}

void UFighterSkeletalMeshComponent::TickPose(float DeltaTime, bool bNeedsValidRootMotion)
{
    
    // Updating the last animation update time.
    LastPoseUpdate += DeltaTime;
    
    // If the last pose update did not reach the pose update frequency we skip.
    if (LastPoseUpdate < PoseUpdateFrequency) {
        return;
    }
    
    // Updating.
    Super::TickPose(LastPoseUpdate, bNeedsValidRootMotion);
    
    // Resetting the last animation update value since we are updating.
    LastPoseUpdate = 0.0f;
}
