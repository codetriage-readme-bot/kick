// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "kick.h"
#include "hero.h"
#include "FighterType.h"
#include "LevelSequence.h"
#include "Engine/DataAsset.h"
#include "Stage.generated.h"


UCLASS(BlueprintType)
class KICK_API UStage : public UDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName Level;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Title;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Location;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (Bitmask, BitmaskEnum = EDeed))
	int32 Requirements;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UHero*> Heroes;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSet<UFighterType*> Enemies;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	USoundCue* Music;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ULevelSequence* Opening;

};
