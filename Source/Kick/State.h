// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "State.generated.h"

UCLASS(Blueprintable, BlueprintType)
class KICK_API UState : public UObject {
    GENERATED_BODY()

 public:
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "StateMachine")
    virtual bool Enter(UObject* Object);
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "StateMachine")
    virtual bool Update(UObject* Object);
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "StateMachine")
    virtual bool Exit(UObject* Object);
};
