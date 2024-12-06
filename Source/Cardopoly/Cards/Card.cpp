#include "Card.h"

#include "FCTween.h"
#include "FCTweenInstance.h"
#include "Cardopoly/Buildings/BuildingPrototypeService.h"
#include "Cardopoly/Buildings/BuildingService.h"
#include "Components/WidgetComponent.h"


ACard::ACard()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ACard::Construct(BuildingService* buildingsController, BuildingPrototypeService* buildingPrototypeService, uint32 id)
{
	_id = id;
	_buildingsService = buildingsController;
	_buildingPrototypeService = buildingPrototypeService;
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

bool ACard::CanApply(FVector2D screenPosition)
{
	return _buildingsService->CanCreateBuildingUnderScreenPosition(screenPosition, _id);
}

void ACard::Apply(FVector2D screenPosition)
{
	flecs::entity buildingEntity;
	_buildingsService->CreateBuildingUnderScreenPosition(screenPosition, _id, buildingEntity);
	
	OnCardAppliedDelegate.Broadcast(this);
}

void ACard::ShowPrototype(FVector2D screenPosition)
{
	_buildingPrototypeService->ShowBuildingPrototype(_id, screenPosition);
}

void ACard::UpdatePrototype(FVector2D ScreenPosition)
{
	_buildingPrototypeService->UpdateBuildingPrototypePosition(ScreenPosition);
}

void ACard::HidePrototype()
{
	_buildingPrototypeService->HideBuildingPrototype();
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

