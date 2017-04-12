// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/DataAsset.h"
#include "Skin.generated.h"

UCLASS(BlueprintType)
class KICK_API USkin : public UDataAsset
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UTexture2D* Portrait;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	USkeletalMesh* Stage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	USkeletalMesh* Map;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (Bitmask, BitmaskEnum = EDeed))
	int32 Requirements;

};
