// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/SkeletalMeshComponent.h"
#include "CustomSkeletalMeshComponent.generated.h"

/**
 * 
 */
UCLASS()
class KICK_API UCustomSkeletalMeshComponent : public USkeletalMeshComponent
{
	GENERATED_UCLASS_BODY()

protected:
    
    float LastAnimationUpdate;
    
public:
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Animation")
    float AnimationUpdateFrequency;
    
//    void TickAnimation(float DeltaTime);
    virtual void TickPose(float DeltaTime, bool bNeedsValidRootMotion) override;
	
};
