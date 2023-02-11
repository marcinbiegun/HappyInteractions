// Copyright SpaceCatLabs. All Rights Reserved.

#include "Utils/HappyUtils.h"

FName HappyUtils::GameplayTagToFName(FGameplayTag InGameplayTag)
{
	if (!InGameplayTag.IsValid())
		return FName();

	const FString VariableString = InGameplayTag.ToString();
	if (VariableString.IsEmpty())
		return FName();

	return FName(VariableString);
}

bool HappyUtils::IsComponentParentedBy(const USceneComponent* InCheckedComponent, const USceneComponent* InParentComponent, const bool bInCheckWholeChain /*= true */)
{
	if (!InCheckedComponent || !InParentComponent)
		return false;

	if (InCheckedComponent == InParentComponent)
		return false;

	if (bInCheckWholeChain)
	{
		TArray<USceneComponent*> ParentComponents;
		InCheckedComponent->GetParentComponents(ParentComponents);
		for (const USceneComponent* ParentComponent : ParentComponents) {
			if (ParentComponent == InParentComponent)
				return true;
		}
	} else
	{
		return InCheckedComponent->GetAttachParent() == InParentComponent;
	}
	
	return false;
}
