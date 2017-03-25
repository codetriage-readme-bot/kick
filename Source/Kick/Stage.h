// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "FighterType.h"
#include "LevelSequence.h"
#include "Engine/DataAsset.h"
#include "Stage.generated.h"


UENUM(BlueprintType, meta = (Bitflags))
enum class EDeed : uint8
{
	Deed0 UMETA(DisplayName = "Escaped Room"),
	Deed1 UMETA(DisplayName = "Saved Silver"),
	Deed2 UMETA(DisplayName = "Changed Costume"),
	Deed3 UMETA(DisplayName = "Left Ramos Behind"),
	Deed4 UMETA(DisplayName = "Defeated Jam Azzar")
};

ENUM_CLASS_FLAGS(EDeed)


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
	TArray<UFighterType*> Heroes;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSet<UFighterType*> Enemies;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	USoundCue* Music;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ULevelSequence* Opening;

};
