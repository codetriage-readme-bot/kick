// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/MovementComponent.h"
#include "FighterMovementComponent.generated.h"

class AFighterPawn;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class KICK_API UFighterMovementComponent : public UMovementComponent
{
    GENERATED_UCLASS_BODY()
    
    UPROPERTY(BlueprintReadWrite, Category="Pawn|Fighter")
    float Drag;

    UPROPERTY(BlueprintReadWrite, Category="Pawn|Fighter")
    float GravityInfluence;
    
    UPROPERTY(BlueprintReadOnly, Category="Pawn|Fighter")
    bool Grounded;
    
    UPROPERTY(BlueprintReadWrite, Category="Pawn|Fighter")
    float TargetDepth;
    
    UPROPERTY(BlueprintReadWrite, Category="Pawn|Fighter")
    bool Frozen;
    
    UFUNCTION(BlueprintCallable, Category="Pawn|Fighter")
    virtual void AddImpulse(FVector NewImpulse);
    
    virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
    
protected:
    
    UPROPERTY()
    uint32 Recursions;

    UPROPERTY()
    FVector Impulse;
    
    UFUNCTION()
    void Move(FVector Delta);
    
    UFUNCTION()
    virtual void UpdateVelocity(float DeltaTime);
    
    UFUNCTION()
    virtual bool IsAbove(UBoxComponent* OtherComponent);
   
	UFUNCTION()
	virtual bool IsFlanking(UBoxComponent* OtherComponent);

    UFUNCTION()
    virtual float GetHorizontalOverlap(UBoxComponent* OtherComponent);
    
};
