// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "BaseFighter.generated.h"

class UBoxComponent;
class USkeletalMeshComponent;
class UFighterMovementComponent;

UCLASS(config=Game, Blueprintable, BlueprintType)
class KICK_API ABaseFighter : public APawn {
	GENERATED_UCLASS_BODY()

    // Public events.
    UFUNCTION(BlueprintImplementableEvent, Category = "Pawn|Fighter")
    void Landed();
    
    UFUNCTION(BlueprintImplementableEvent, Category = "Pawn|Fighter")
    void Jumped();
    
private_subobject:
	UPROPERTY(Category = Pawn, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UBoxComponent* CollisionComponent;

	UPROPERTY(Category = Pawn, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* MeshComponent;

private:
    UPROPERTY(Category = Pawn, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
    UFighterMovementComponent* MovementComponent;

protected:
    
    // Protected variables.
    float JiggleDuration;
    
public:
	ABaseFighter();
    
    static FName MeshComponentName;
    static FName MovementComponentName;
    static FName CollisionComponentName;
    
    // Public overrides.
    virtual void PostInitializeComponents() override;
    virtual UPawnMovementComponent* GetMovementComponent() const override;
    virtual void Tick(float DeltaSeconds) override;
    
    // Public new methods.
    UBoxComponent* GetCollisionComponent() const;
	USkeletalMeshComponent* GetMeshComponent() const;
    
    UFUNCTION(BlueprintCallable, Category="Pawn|Fighter")
    virtual void Jiggle(float Duration);
};
