// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Move.h"
#include "GameFramework/GameMode.h"
#include "StageModeBase.generated.h"


UCLASS(config = Game, notplaceable, BlueprintType, Blueprintable, Transient, hideCategories = (Info, Rendering, MovementReplication, Replication, Actor), meta = (ShortTooltip = "Game Mode defines the game being played, its rules, scoring, and other facets of the game type."))
class KICK_API AStageModeBase : public AGameMode
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "GameMode|Stage")
	TArray<UMove*> Moves;	

	UFUNCTION(BlueprintCallable, Category = "Game")
	virtual void StartPlay() override;
};
