#pragma once

#include "State.h"
#include "Components/ActorComponent.h"
#include "StateMachineComponent.generated.h"

UCLASS(EditInlineNew, meta=(BlueprintSpawnableComponent))
class KICK_API UStateMachineComponent : public UActorComponent
{
	GENERATED_UCLASS_BODY()
    
public:
	
	/** Flag to define if the state machine is enabled or not. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool Disabled;
    
    /** Flag to define if the state machine is enabled or not. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool Debug;
    
    /** Set current state. */
    UFUNCTION(BlueprintCallable, Category="Components|StateMachine")
    void SetState(TSubclassOf<UState> State);
    
    /** Revert to previous state. */
    UFUNCTION(BlueprintCallable, Category="Components|StateMachine")
    void RevertState();

    /** Update the current state. */
    UFUNCTION(BlueprintCallable, Category="Components|StateMachine")
    void UpdateState();
    
    /** Update the current state. */
    UFUNCTION(BlueprintCallable, Category="Components|StateMachine")
    TSubclassOf<UState> GetState();
    
    UState* TestState;
    
protected:
    
    /** The current state. */
    UState* CurrentState;
    
    /** The previous state. */
    UState* PreviousState;

};
