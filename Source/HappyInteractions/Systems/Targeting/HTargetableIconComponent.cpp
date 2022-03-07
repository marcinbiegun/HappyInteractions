// Copyright SpaceCatLabs. All Rights Reserved.

#include "HTargetableIconComponent.h"

#include "HTargetableComponent.h"

DEFINE_LOG_CATEGORY(LogHUserInterface);

UHTargetableIconComponent::UHTargetableIconComponent()
{
	SetWidgetSpace(EWidgetSpace::Screen);
	SetDrawSize(FVector2D(50.f, 50.f));
}

void UHTargetableIconComponent::BeginPlay()
{
	Super::BeginPlay();

	UUserWidget* WidgetInstance = GetUserWidgetObject();
	if (!WidgetInstance)
	{
		UE_LOG(LogHUserInterface, Error, TEXT("Widget missing in HTargetableIconComponent"));
	}
	else
	{
		UHTargetableIconUserWidget* CastedWidgetInstance = Cast<UHTargetableIconUserWidget>(WidgetInstance);
		if (!CastedWidgetInstance)
		{
			UE_LOG(LogHUserInterface, Error, TEXT("Widget instance found but unable to cast it to HTargetableIconUserWdiget"));
		}
		else
		{
			TargetableIconUserWidget = CastedWidgetInstance;
		}
	}
	
	Hide();
}

void UHTargetableIconComponent::Show() const
{
	if (TargetableIconUserWidget)
		TargetableIconUserWidget->OnShow();
}

void UHTargetableIconComponent::Hide() const
{
	if (TargetableIconUserWidget)
		TargetableIconUserWidget->OnHide();
}

void UHTargetableIconComponent::Selected() const
{
	if (TargetableIconUserWidget)
		TargetableIconUserWidget->OnSelected();
}

void UHTargetableIconComponent::Unselected() const
{
	if (TargetableIconUserWidget)
		TargetableIconUserWidget->OnUnselected();
}

void UHTargetableIconComponent::OutOfReach() const
{
	if (TargetableIconUserWidget)
		TargetableIconUserWidget->OnOutOfReach();
}

void UHTargetableIconComponent::SetForceHidden(bool bInHidden) const
{
	if (TargetableIconUserWidget)
		TargetableIconUserWidget->OnSetForceHidden(bInHidden);
}

