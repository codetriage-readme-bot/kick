// Fill out your copyright notice in the Description page of Project Settings.

#include "Kick.h"
#include "EngineUtils.h"
#include "StageModeBase.h"


AStageModeBase::AStageModeBase(const FObjectInitializer& ObjectInitializer) {
	TArray<UObject*> Assets;
	EngineUtils::FindOrLoadAssetsByPath(TEXT("/Game/Data/Moves"), Assets, EngineUtils::ATL_Regular);
	UE_LOG(LogTemp, Warning, TEXT("Lenght %d"), Assets.Num());
	for (UObject* Asset : Assets)
	{
		UMove* Move = Cast<UMove>(Asset);
		if (Move)
		{
			Moves.Add(Move);
		}
	}
}

void AStageModeBase::StartPlay()
{
	TArray<UObject*> Assets;
	EngineUtils::FindOrLoadAssetsByPath(TEXT("/Game/Data/Moves"), Assets, EngineUtils::ATL_Regular);
	UE_LOG(LogTemp, Warning, TEXT("Lenght %d"), Assets.Num());
	for (UObject* Asset : Assets)
	{
		UMove* Move = Cast<UMove>(Asset);
		UE_LOG(LogTemp, Warning, TEXT("Storing Move"));
		if (Move)
		{
			Moves.Add(Move);
		}
	}

	Super::StartPlay();
}