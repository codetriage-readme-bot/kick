// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"


UENUM(BlueprintType)
enum class ECharacter : uint8
{
	Generic,
	Keni,
	Ramos,
	Tonka,
	Silver
};


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


UENUM(BlueprintType, meta = (Bitflags))
enum class EDeed : uint8
{
	Deed0 UMETA(DisplayName = "Met Keni"),
	Deed1 UMETA(DisplayName = "Met Tonka"),
	Deed2 UMETA(DisplayName = "Beat K1"),
	Deed4 UMETA(DisplayName = "Beat T1"),
	Deed5 UMETA(DisplayName = "Escaped")
};

ENUM_CLASS_FLAGS(EDeed)