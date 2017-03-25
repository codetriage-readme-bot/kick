// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "FighterPawn.h"
#include "Engine/DataAsset.h"
#include "Move.generated.h"


UENUM(BlueprintType, meta = (Bitflags))
enum class EMoveType : uint8
{
	Stance,
	Locomotion,
	Impulsion,
	Transition,
	Guard,
	Damage,
	Basic,
	Special,
	Super
};

ENUM_CLASS_FLAGS(EMoveType)


UENUM(BlueprintType)
enum class EBlockLevel : uint8
{
	None,
	Stance,
	Locomotion,
	Impulsion,
	Transition,
	Basic,
	Special,
	Super
};


UENUM(BlueprintType, meta = (Bitflags))
enum class ELocalInput : uint8
{
	Neutral,
	Up,
	Down,
	Back,
	Forward,
	UpBack,
	UpForward,
	DownBack,
	DownForward,
	LightPunch,
	FiercePunch,
	LightKick,
	FierceKick,
	Modifier,
	StafeUp,
	StrafeDown,
	FlipLeft,
	FlipRight
};

ENUM_CLASS_FLAGS(ELocalInput)


UENUM(BlueprintType, meta = (Bitflags))
enum class EInputState : uint8
{
	Pressed,
	Released
};

ENUM_CLASS_FLAGS(EInputState)


UENUM(BlueprintType)
enum class EModiferState : uint8
{
	Any,
	Pressed,
	Released
};


UENUM(BlueprintType, meta = (Bitflags))
enum class EFighterState : uint8
{
	Standing,
	Crouching,
	Jumping
};

ENUM_CLASS_FLAGS(EFighterState)


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


UCLASS(BlueprintType)
class KICK_API UMove : public UDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EMoveType Type;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EFighterState State;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (Bitmask, BitmaskEnum = EMoveType))
	int32 Disables;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool Loop;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FTrigger> Triggers;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool Vulnerable;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UMove* ReversalMove;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSet<UMove*> PossibleMoves;

};
