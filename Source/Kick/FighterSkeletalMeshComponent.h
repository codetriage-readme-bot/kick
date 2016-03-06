// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/SkeletalMeshComponent.h"
#include "FighterSkeletalMeshComponent.generated.h"

/**
 * 
 */
UCLASS()
class KICK_API UFighterSkeletalMeshComponent : public USkeletalMeshComponent
{
	GENERATED_UCLASS_BODY()

protected:
    
    float LastPoseUpdate;
    
public:
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Animation")
    float PoseUpdateFrequency;
    
//  virtual void TickAnimation(float DeltaTime);
    virtual void TickPose(float DeltaTime, bool bNeedsValidRootMotion) override;
	
};
