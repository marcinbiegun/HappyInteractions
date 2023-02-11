// Copyright SpaceCatLabs. All Rights Reserved.

#include "Variable/HappyVariableSubsystem.h"

void UHappyVariableSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UHappyVariableSubsystem::Deinitialize()
{
	Super::Deinitialize();
}

int32 UHappyVariableSubsystem::Get(FName InName)
{
	if (Variables.Contains(InName))
	{
		return Variables[InName];
	}
	return 0;
}

int32 UHappyVariableSubsystem::IsTrue(FName InName)
{
	if (Variables.Contains(InName))
	{
		return Variables[InName] > 0;
	}
	return false;
}

int32 UHappyVariableSubsystem::IsFalse(FName InName)
{
	return !IsTrue(InName);
}

int32 UHappyVariableSubsystem::Set(FName InName, int32 InValue)
{
	if (InValue != Get(InName))
	{
		Variables.Add(InName, InValue);
		BroadcastUpdate(InName, InValue);
	}
	return InValue;
}

int32 UHappyVariableSubsystem::SetTrue(FName InName)
{
	const int32 CurrentValue = Get(InName);
	if (CurrentValue > 0)
	{
		return CurrentValue;
	}
	
	return Set(InName, 1);
}

int32 UHappyVariableSubsystem::SetFalse(FName InName)
{
	return Clear(InName);
}

int32 UHappyVariableSubsystem::Clear(FName InName)
{
	if (Get(InName) != 0)
	{
		Variables.Remove(InName);
		BroadcastUpdate(InName, 0);
	}
	return 0;
}

int32 UHappyVariableSubsystem::Increment(FName InName)
{
	const int32 NewValue = Get(InName) + 1;
	Set(InName, NewValue);
	BroadcastUpdate(InName, NewValue);
	return NewValue;
}

int32 UHappyVariableSubsystem::Decrement(FName InName)
{
	const int32 NewValue = Get(InName) - 1;
	Set(InName, NewValue);
	BroadcastUpdate(InName, NewValue);
	return NewValue;
}

FHappyOnVariableChange& UHappyVariableSubsystem::GetOnUpdateDelegate(const FName InKey)
{
	return OnChangeDelegates.FindOrAdd(InKey, FHappyOnVariableChange{});
}

FHappyOnVariableChange& UHappyVariableSubsystem::GetOnAnyUpdateDelegate()
{
	return OnAnyChangeDelegate;
}

void UHappyVariableSubsystem::BroadcastUpdate(const FName InKey, const int32 InValue)
{
	if (const FHappyOnVariableChange* UpdateDelegate = OnChangeDelegates.Find(InKey))
	{
		UpdateDelegate->Broadcast(InKey, InValue);
	}

	OnAnyChangeDelegate.Broadcast(InKey, InValue);
}
