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

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Charge;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (Bitmask, BitmaskEnum = ELocalInput))
	int32 Validation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EInputState State;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool Changed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (Bitmask, BitmaskEnum = EInputState))
	int32 Modifier;

	FTrigger()
	{
		Charge = 0;
		Changed = false;
	}

};


USTRUCT(BlueprintType)
struct FMotion {

	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool Inherit;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector2D Impulse;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool WillLand;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Gravity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Drag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EStrafe Strafe;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool Flip;

	FMotion()
	{
		Gravity = 1.0f;
	}

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
	TArray<FMotion> Motions;

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


USTRUCT(BlueprintType)
struct FHit {

	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite)
	bool Landed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Damage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Freeze;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Shake;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USoundBase* Sound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector2D Force;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ERepercussion Repercussion;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EStrength Strength;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EElement Element;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (Bitmask, BitmaskEnum = EFighterState))
	int32 Break;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UMove*> Targets;

};