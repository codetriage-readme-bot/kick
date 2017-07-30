// Fill out your copyright notice in the Description page of Project Settings.

#include "Kick.h"
#include "CustomGameInstance.h"


void UCustomGameInstance::Init()
{
	TMap<FString, UMove*> Moves;
	TArray<UObject*> Assets;
	EngineUtils::FindOrLoadAssetsByPath(TEXT("/Game/Data/Moves"), Assets, EngineUtils::ATL_Regular);
	for (UObject* Asset : Assets)
	{
		UMove* Move = Cast<UMove>(Asset);
		if (Move)
		{
			Moves.Add(Move->GetName(), Move);
		}
	}
	TArray<FString> Keys;
	Moves.GetKeys(Keys);

	Assets.Empty();
	EngineUtils::FindOrLoadAssetsByPath(TEXT("/Game/Data/Profiles"), Assets, EngineUtils::ATL_Regular);
	for (UObject* Asset : Assets)
	{
		UFighterType* Fighter = Cast<UFighterType>(Asset);
		if (Fighter)
		{

			// Registering animations.
			FAnimationSet AnimationSet;
			TArray<UObject*> AnimationAssets;
			EngineUtils::FindOrLoadAssetsByPath(FString::Printf(TEXT("/Game/Animations/%s"), *Fighter->GetName()), AnimationAssets, EngineUtils::ATL_Regular);
			for (UObject* AnimationAsset : AnimationAssets) {
				UAnimSequenceBase* Animation = Cast<UAnimSequenceBase>(AnimationAsset);
				if (Animation)
				{
					UMove** Move = Moves.Find(Animation->GetName());
					if (Move)
					{
						UE_LOG(LogTemp, Warning, TEXT("%s registered %s"), *Fighter->GetName(), *Animation->GetName());
						AnimationSet.Animations.Add(*Move, Animation);
					}
				}
			}
			
			// Storing the fighter animation map.
			Animations.Add(Fighter, AnimationSet);
		}
	}

	

	Super::Init();
}


