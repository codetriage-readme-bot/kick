// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PawnMovementComponent.h"
#include "FighterMovementComponent.generated.h"

UCLASS(meta = (BlueprintSpawnableComponent))
class KICK_API UFighterMovementComponent : public UPawnMovementComponent {
    
	GENERATED_UCLASS_BODY()
    
    // Public overrides.
    virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
    virtual bool IsMovingOnGround() const override;

   // Public methods.
    UFUNCTION(BlueprintCallable, Category="Pawn|Fighter")
    virtual void SetVelocity(FVector NewVelocity);
    
    UFUNCTION(BlueprintCallable, Category="Pawn|Fighter")
    virtual void SetFrozen(bool NewFrozen);

    UFUNCTION(BlueprintCallable, Category="Pawn|Fighter")
    virtual void AddImpulse(FVector AddedImpulse);

    UFUNCTION(BlueprintCallable, Category="Pawn|Fighter")
    virtual void SetDestination(FVector NewDestination);
    
    // Public properties.
    static const float MIN_FLOOR_DIST;

protected:

    // Protected overrides.
    virtual bool ResolvePenetrationImpl(const FVector& Adjustment, const FHitResult& Hit, const FQuat& NewRotation) override;
    
    // Protected methods.
    virtual bool LimitWorldBounds();

    // Protected properties.
    UPROPERTY(Transient)
    uint32 bPositionCorrected:1;

    UPROPERTY(Transient)
    uint32 bGrounded:1;
    
    UPROPERTY(Transient)
    uint32 bFrozen:1;

    UPROPERTY(Transient)
    uint32 bHasDestination:1;
    
    UPROPERTY()
    FVector Destination;
    
    UPROPERTY()
    FVector Cruise;
};
