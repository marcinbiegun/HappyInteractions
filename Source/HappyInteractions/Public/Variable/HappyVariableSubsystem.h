#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "HappyVariableSubsystem.generated.h"

struct FGameplayTag;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FHappyOnVariableChange, FName, Name, int32, Value);


/**
 * This subsystem stores game variables.
 *
 * Keys are strings, values are integers.
 * Returned value is always an integer, when variable is missing, 0 value is returned.
 * Values can be negative.
 * Zero and negative numbers are considered to be FALSE, positive numbers are TRUE.
 */
UCLASS()
class HAPPYINTERACTIONS_API UHappyVariableSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	UFUNCTION(BlueprintPure)
	int32 Get(FName InName);

	UFUNCTION(BlueprintPure)
	int32 IsTrue(FName InName);
	
	UFUNCTION(BlueprintPure)
	int32 IsFalse(FName InName);
	
	UFUNCTION(BlueprintCallable)
	int32 Set(FName InName, int32 InValue);
	
	UFUNCTION(BlueprintCallable)
	int32 SetTrue(FName InName);
	
	UFUNCTION(BlueprintCallable)
	int32 SetFalse(FName InName);
	
	UFUNCTION(BlueprintCallable)
	int32 Clear(FName InName);
	
	UFUNCTION(BlueprintCallable)
	int32 Increment(FName InName);
	
	UFUNCTION(BlueprintCallable)
	int32 Decrement(FName InName);
	
	FHappyOnVariableChange& GetOnUpdateDelegate(FName InKey);
	FHappyOnVariableChange& GetOnAnyUpdateDelegate();

protected:

	UPROPERTY()
	TMap<FName, int32> Variables;
	
	UPROPERTY()
	TMap<FName, FHappyOnVariableChange> OnChangeDelegates;
	
	FHappyOnVariableChange OnAnyChangeDelegate = FHappyOnVariableChange();

	void BroadcastUpdate(const FName InKey, const int32 InValue);
};


