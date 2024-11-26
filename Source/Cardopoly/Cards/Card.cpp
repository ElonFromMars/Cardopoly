#include "Card.h"

#include "FCTween.h"
#include "FCTweenInstance.h"
#include "Cardopoly/Buildings/BuildingService.h"
#include "Components/WidgetComponent.h"


ACard::ACard()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ACard::Construct(BuildingService* buildingsController, uint32 id)
{
	_id = id;
	BuildingsController = buildingsController;
	const auto WidgetComponent = this->GetComponentByClass<UWidgetComponent>();
	CardWidget = StaticCast<UCardWidget*>(WidgetComponent->GetUserWidgetObject());
	WidgetComponent->RequestRenderUpdate();
}

void ACard::BeginPlay()
{
	Super::BeginPlay();
}

void ACard::BeginDestroy()
{
	if (Tween != nullptr)
	{
		Tween->Destroy();
		Tween = nullptr;
	}
	
	Super::BeginDestroy();
}

void ACard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

bool ACard::CanApply(FVector2D ScreenPosition)
{
	return BuildingsController->CanCreateBuildingUnderScreenPosition(ScreenPosition);
}

void ACard::Apply(FVector2D ScreenPosition)
{
	ABuilding* Building;
	BuildingsController->CreateBuildingUnderScreenPosition(ScreenPosition, _id, Building);
	
	OnCardAppliedDelegate.Broadcast(this);
}

void ACard::StopMovement()
{
	if(Tween)
	{
		Tween->Destroy();
	}
}


void ACard::MoveToPosition(FVector Position, float Duration, EFCEase EaseType)
{
	StopMovement();
	Tween = FCTween::Play(this->GetActorLocation(), Position,
		[&](FVector t)
		{
			SetActorLocation(t);
		}, Duration,
	EaseType);
}

void ACard::MoveToLocalPosition(FVector LocalPosition, float Duration, EFCEase EaseType)
{
	StopMovement();
	Tween = FCTween::Play(this->GetRootComponent()->GetRelativeLocation(), LocalPosition,
		[&](FVector t)
		{
			SetActorRelativeLocation(t);
		}, Duration,
	EaseType);
}

