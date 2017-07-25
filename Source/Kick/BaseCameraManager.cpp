// Fill out your copyright notice in the Description page of Project Settings.

#include "Kick.h"
#include "BaseCameraManager.h"

void ABaseCameraManager::SetAnimCameraActor(ACameraActor* camera) {
	AnimCameraActor = camera;
}

ACameraActor* ABaseCameraManager::GetAnimCameraActor() {
	return AnimCameraActor;
}

