// Copyright SpaceCatLabs. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "HTargetableIconUserWidget.h"
#include "HTargetableIconComponent.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogHUserInterface, Log, All);

/**
 * This component displays interaction icons.
 *
 * It requires to have TargetableComponent as a parent component to work properly.
 */
UCLASS(Blueprintable)
class UHTargetableIconComponent : public UWidgetComponent
{
	GENERATED_BODY()

	UHTargetableIconComponent();

	virtual void BeginPlay() override;

public:
	
	void Show() const;
	void Hide() const;
	void Selected() const;
	void Unselected() const;
	void OutOfReach() const;
	void SetForceHidden(bool bInHidden) const;

protected:

	UPROPERTY(Transient)
	UHTargetableIconUserWidget* TargetableIconUserWidget;

};

