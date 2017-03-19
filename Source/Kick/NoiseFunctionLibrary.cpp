// Fill out your copyright notice in the Description page of Project Settings.

#include "Kick.h"
#include "NoiseFunctionLibrary.h"

float UNoiseFunctionLibrary::Random(int32 seconds, int32 seed) {
    int32 n = seconds + seed * 57;
    n = n << 13 ^ n;
    return (float)(1.0 - ((n * (n * n * 15731 + 789221) + 1376312589) & 0x7fffffff)) / 1073741824.0;
}

float UNoiseFunctionLibrary::Cerp(float a, float b, float blend) {
    float ft = blend * 3.1415927;
    float f = (1 - cos(ft)) * 0.5;
    return a * (1 - f) + b * f;
}

float UNoiseFunctionLibrary::Lerp(float a, float b, float blend) {
    return a * (1 - blend) + b * blend;
}

float UNoiseFunctionLibrary::SimpleNoise(float seconds, float amplitude, float frequency, int32 seed) {
    seconds *= frequency;

    // TODO: This is always worth 0 for some reason.
    int32 integer = (int32)seconds;
    float remainder = seconds - integer;
    float ret = Cerp(Random(integer, seed), Random(integer + 1, seed), remainder) * amplitude;

    // UE_LOG(LogTemp, Warning, TEXT("Seconds: %f Time: %f"), seconds, integer);
    return ret;
}


