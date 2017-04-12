// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Move.h"
#include "FighterType.h"
#include "Engine/GameInstance.h"
#include "CustomGameInstance.generated.h"

USTRUCT(BlueprintType)
struct FAnimationSet {

	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<UMove*, UAnimSequenceBase*> Animations;
};

UCLASS(config = Game, transient, BlueprintType, Blueprintable)
class KICK_API UCustomGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<UFighterType*, FAnimationSet> Animations;

	virtual void Init() override;
};
