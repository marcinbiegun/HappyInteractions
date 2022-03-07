// Copyright SpaceCatLabs. All Rights Reserved.

#include "HGameVariableSubsystem.h"

void UHGameVariableSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	// Collection.InitializeDependency(URogerioGIS::StaticClass());
	UE_LOG(LogTemp, Warning, TEXT("Variables Subsystem init."));
}

void UHGameVariableSubsystem::Deinitialize()
{
	Super::Deinitialize();
}

int32 UHGameVariableSubsystem::Get(FName InName)
{
	if (Variables.Contains(InName))
	{
		return Variables[InName];
	}
	return 0;
}

int32 UHGameVariableSubsystem::IsTrue(FName InName)
{
	if (Variables.Contains(InName))
	{
		return Variables[InName] > 0;
	}
	return false;
}

int32 UHGameVariableSubsystem::IsFalse(FName InName)
{
	return !IsTrue(InName);
}

int32 UHGameVariableSubsystem::Set(FName InName, int32 InValue)
{
	if (InValue != Get(InName))
	{
		Variables.Add(InName, InValue);
		BroadcastUpdate(InName, InValue);
	}
	return InValue;
}

int32 UHGameVariableSubsystem::SetTrue(FName InName)
{
	const int32 CurrentValue = Get(InName);
	if (CurrentValue > 0)
	{
		return CurrentValue;
	}
	
	return Set(InName, 1);
}

int32 UHGameVariableSubsystem::SetFalse(FName InName)
{
	return Clear(InName);
}

int32 UHGameVariableSubsystem::Clear(FName InName)
{
	if (Get(InName) != 0)
	{
		Variables.Remove(InName);
		BroadcastUpdate(InName, 0);
	}
	return 0;
}

int32 UHGameVariableSubsystem::Increment(FName InName)
{
	const int32 NewValue = Get(InName) + 1;
	Set(InName, NewValue);
	BroadcastUpdate(InName, NewValue);
	return NewValue;
}

int32 UHGameVariableSubsystem::Decrement(FName InName)
{
	const int32 NewValue = Get(InName) - 1;
	Set(InName, NewValue);
	BroadcastUpdate(InName, NewValue);
	return NewValue;
}

FHVariableUpdateDelegate& UHGameVariableSubsystem::GetOnUpdateDelegate(const FName InKey)
{
	return OnChangeDelegates.FindOrAdd(InKey, FHVariableUpdateDelegate{});
}

FHVariableUpdateDelegate& UHGameVariableSubsystem::GetOnAnyUpdateDelegate()
{
	return OnAnyChangeDelegate;
}

void UHGameVariableSubsystem::BroadcastUpdate(const FName InKey, const int32 InValue)
{
	if (const FHVariableUpdateDelegate* UpdateDelegate = OnChangeDelegates.Find(InKey))
	{
		UpdateDelegate->Broadcast(InKey, InValue);
	}

	OnAnyChangeDelegate.Broadcast(InKey, InValue);
}
