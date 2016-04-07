// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "FighterPawn.generated.h"

class UBoxComponent;
class UFighterSkeletalMeshComponent;
class UFighterMovementComponent;

UCLASS(config=Game, Blueprintable, BlueprintType)
class KICK_API AFighterPawn : public APawn {
	GENERATED_UCLASS_BODY()

    AFighterPawn();
    
    static FName MeshComponentName;
    static FName MovementComponentName;
    static FName CollisionComponentName;

    UPROPERTY(Category = Pawn, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
    UBoxComponent* CollisionComponent;
    
    UPROPERTY(Category = Pawn, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
    UFighterSkeletalMeshComponent* MeshComponent;
    
    UPROPERTY(Category = Pawn, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
    UFighterMovementComponent* MovementComponent;
    
    UPROPERTY(BlueprintReadOnly, Category="Pawn|Fighter")
    bool Grounded;
    
    virtual void PostInitializeComponents() override;
    
    virtual void Tick(float DeltaSeconds) override;
    
    UFUNCTION(BlueprintCallable, Category="Pawn|Fighter")
    virtual void Jiggle(float Duration);

    UFUNCTION(BlueprintImplementableEvent, Category = "Pawn|Fighter")
    void Landed();
    
protected:
    
    float JiggleDuration;
    
public:
    

};
