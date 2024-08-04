#include "HandAnimationComponent.h"

#include "Hand.h"


UHandAnimationComponent::UHandAnimationComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UHandAnimationComponent::BeginPlay()
{
	Super::BeginPlay();
	Hand = static_cast<AHand*>(GetOwner());
	Hand->OnDrawCardDelegate.AddUniqueDynamic(this, &ThisClass::OnDrawCard);
}

void UHandAnimationComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                            FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

