// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Camera/PlayerCameraManager.h"
#include "BaseCameraManager.generated.h"

/**
 * 
 */
UCLASS()
class KICK_API ABaseCameraManager : public APlayerCameraManager
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable)
	void SetAnimCameraActor(ACameraActor* camera);

	UFUNCTION(BlueprintCallable)
	ACameraActor* GetAnimCameraActor();

};
