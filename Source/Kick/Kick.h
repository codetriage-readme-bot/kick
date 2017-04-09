// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"

UENUM(BlueprintType, meta = (Bitflags))
enum class EMoveType : uint8
{
	Stance,
	Locomotion,
	Attack,
	Special,
	Super
};

ENUM_CLASS_FLAGS(EMoveType)


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
	Deed5 UMETA(DisplayName = "Escaped"),
	Deed6 UMETA(DisplayName = "Unlocked a Thing")
};

ENUM_CLASS_FLAGS(EDeed)


//UENUM(BlueprintType)
//enum class EElement : uint8
//{
//	None,
//	Fire,
//	Electricty,
//	Ice,
//	Gas,
//	Water,
//	Poison
//};
//
//
//UENUM(BlueprintType)
//enum class EStrength : uint8
//{
//	Light,
//	Fierce
//};
//
//
//UENUM(BlueprintType)
//enum class ERepercussion : uint8
//{
//	None,
//	Swipe,
//	Project
//};
//
//
//UENUM(BlueprintType)
//enum class EStrafe : uint8
//{
//	None,
//	Up,
//	Down,
//	Top,
//	Bottom
//};