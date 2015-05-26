// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "NoiseFunctionLibrary.generated.h"

UCLASS()
class KICK_API UNoiseFunctionLibrary : public UBlueprintFunctionLibrary {
    GENERATED_BODY()

 public:
    UFUNCTION(BlueprintCallable, Category = "NoiseFunctionLibrary")
    static float SimpleNoise(float seconds, float amplitude, float frequency, int32 seed);

 protected:
    static float Random(int32 seconds, int32 seed);
    static float Lerp(float a, float b, float blend);
    static float Cerp(float a, float b, float blend);
};
