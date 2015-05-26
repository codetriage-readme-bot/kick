// Fill out your copyright notice in the Description page of Project Settings.

#include "Kick.h"
#include "State.h"
#include "StateMachineComponent.h"

UStateMachineComponent::UStateMachineComponent(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer) {
    CurrentState = nullptr;
    PreviousState = nullptr;
    TestState = nullptr;
}

void UStateMachineComponent::SetState(TSubclassOf<UState> State) {
    PreviousState = CurrentState;
    CurrentState = (UState*)State->GetDefaultObject(true);
    if (PreviousState && !Disabled) {
        if (Debug) {
            UE_LOG(LogTemp, Warning, TEXT("Exiting State"));
        }
        PreviousState->Exit(GetOwner());
    }
    if (!Disabled) {
        if (Debug) {
            UE_LOG(LogTemp, Warning, TEXT("Entering State"));
        }
        CurrentState->Enter(GetOwner());
    }
}

void UStateMachineComponent::RevertState() {
    if (PreviousState) {
        SetState(PreviousState->GetClass());
    }
}

void UStateMachineComponent::UpdateState() {
    if (CurrentState && !Disabled) {
        CurrentState->Update(GetOwner());
    }
}

TSubclassOf<UState> UStateMachineComponent::GetState() {
    return CurrentState->GetClass();
}

