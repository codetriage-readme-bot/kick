// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "FighterPawn.generated.h"

class UAnimMontage;
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

    UPROPERTY()
    UAnimMontage* AnimMontage;

    virtual void PostInitializeComponents() override;
    
    virtual void Tick(float DeltaSeconds) override;

    UFUNCTION(BlueprintCallable, Category=Animation)
    virtual float PlayAnimMontage(class UAnimMontage* AnimMontage, float InPlayRate = 1.f, FName StartSectionName = NAME_None);

    UFUNCTION(BlueprintCallable, Category=Animation)
    virtual void StopAnimMontage(class UAnimMontage* AnimMontage = NULL);

    UFUNCTION(BlueprintCallable, Category=Animation)
    class UAnimMontage * GetCurrentMontage();

    UFUNCTION(BlueprintCallable, Category="Pawn|Fighter")
    virtual void Jiggle(float Duration);

    UFUNCTION(BlueprintImplementableEvent, Category = "Pawn|Fighter")
    void Landed();
    
protected:
    
    float JiggleDuration;

};
