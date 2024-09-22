#include "CardViewComponent.h"

#include "Components/TextRenderComponent.h"
#include "Components/Widget.h"

UCardViewComponent::UCardViewComponent()
{
	
	PrimaryComponentTick.bCanEverTick = true;
}

void UCardViewComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UCardViewComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UCardViewComponent::SetDescriptionText(const FText& Value) const
{
	
}

void UCardViewComponent::SetNameText(const FText& Value) const
{
	
}

void UCardViewComponent::SetCostText(const FText& Value) const
{
	
}

