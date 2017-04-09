// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "kick.h"
#include "FighterPawn.h"
#include "LevelSequence.h"
#include "Engine/DataAsset.h"
#include "Move.generated.h"


USTRUCT(BlueprintType)
struct FTrigger {

	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<ELocalInput> Sequence;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Charge;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (Bitmask, BitmaskEnum = ELocalInput))
	int32 Validation;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EInputState State;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool Changed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (Bitmask, BitmaskEnum = EInputState))
	int32 Modifier;

	FTrigger()
	{
		Charge = 0;
		Changed = false;
	}

};


USTRUCT(BlueprintType)
struct FHit {

	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USoundBase* Sound;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Damage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Freeze;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Shake;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FVector2D Force;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ERepercussion Repercussion;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EStrength Strength;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EElement Element;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (Bitmask, BitmaskEnum = EFighterState))
	int32 Break;

};


USTRUCT(BlueprintType)
struct FMotion {

	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool Inherit;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FVector2D Impulse;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool WillLand;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Gravity;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Drag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EStrafe Strafe;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool Flip;

};


UCLASS(BlueprintType)
class KICK_API UMove : public UDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EMoveType Type;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (Bitmask, BitmaskEnum = EMoveType))
	int32 Disables;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EFighterState State;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool Invincible;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FMotion Motion;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSet<UMove*> PossibleMoves;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Conditions")
	float Energy;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (Bitmask, BitmaskEnum = EDeed), Category = "Conditions")
	int32 Requirements;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Conditions")
	TArray<FTrigger> Triggers;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Animation")
	bool Loop;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation")
	ULevelSequence* Cinematic;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Animation")
	UMove* Reversal;

};
