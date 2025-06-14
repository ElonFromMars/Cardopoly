#include "Card.h"

#include "FCTween.h"
#include "FCTweenInstance.h"
#include "Cardopoly/Buildings/BuildingPrototypeService.h"
#include "Cardopoly/Buildings/BuildingService.h"
#include "Cardopoly/ECS/Core/Cards/Components/ApplyCardRequest.hpp"
#include "Cardopoly/ECS/Core/Cards/Components/BuildingCardComponent.hpp"
#include "Cardopoly/Grid/PositionConversionService.h"
#include "Components/WidgetComponent.h"


ACard::ACard()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ACard::Construct(
	BuildingService* buildingsService,
	PositionConversionService* positionConversionService,
	BuildingPrototypeService* buildingPrototypeService,
	flecs::entity entity
	)
{
	_buildingsService = buildingsService;
	_entity = entity;
	_positionConversionService = positionConversionService;
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
	//TODO rewrite
	if (!_entity.has<BuildingCardComponent>()) return true;
	
	uint32 id = static_cast<uint32>(_entity.get<BuildingCardComponent>()->BuildingId);
	return _buildingsService->CanCreateBuildingUnderScreenPosition(screenPosition, id);
}

void ACard::Apply(FVector2D screenPosition)
{
	FIntVector cellPosition;
	if(_positionConversionService->ScreenPointToGroundPosition(screenPosition, cellPosition))
	{
		_entity.set<ApplyCardRequest>({ cellPosition });
		OnCardAppliedDelegate.Broadcast(this);
	}
}

void ACard::ShowPrototype(FVector2D screenPosition)
{
	//TODO rewrite
	if (!_entity.has<BuildingCardComponent>()) return;
	
	uint32 id = static_cast<uint32>(_entity.get<BuildingCardComponent>()->BuildingId);
	_buildingPrototypeService->ShowBuildingPrototype(id, screenPosition);
}

void ACard::UpdatePrototype(FVector2D ScreenPosition)
{
	//TODO rewrite
	if (!_entity.has<BuildingCardComponent>()) return;
	
	_buildingPrototypeService->UpdateBuildingPrototypePosition(ScreenPosition);
}

void ACard::HidePrototype()
{
	//TODO rewrite
	if (!_entity.has<BuildingCardComponent>()) return;
	
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

