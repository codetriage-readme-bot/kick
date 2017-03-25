// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Move.h"
#include "Engine/DataAsset.h"
#include "FighterType.generated.h"


UCLASS(BlueprintType)
class KICK_API UFighterType : public UDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	USkeletalMesh* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Health;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TMap<UMove*, UAnimSequenceBase*> Animations;
	
};