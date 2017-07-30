// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "kick.h"
#include "Move.h"
#include "Engine/DataAsset.h"
#include "FighterType.generated.h"


UCLASS(BlueprintType)
class KICK_API UFighterType : public UDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Appearance")
	UTexture2D* Portrait;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Appearance")
	USkeletalMesh* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Appearance")
	USkeletalMesh* Pawn;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Appearance")
	FLinearColor Color;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Appearance")
	UMaterialInterface* Trail;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gameplay")
	float Health;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gameplay")
	float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (Bitmask, BitmaskEnum = EDeed))
	int32 Requirements;

};