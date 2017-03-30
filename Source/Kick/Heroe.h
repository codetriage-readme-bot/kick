// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "kick.h"
#include "FighterType.h"
#include "Engine/DataAsset.h"
#include "Heroe.generated.h"


UCLASS(BlueprintType)
class KICK_API UHeroe : public UDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSet<UFighterType*> Fighters;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FColor Color;

};
