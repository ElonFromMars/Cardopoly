#include "Card.h"

#include "Cardopoly/Buildings/BuildingsController.h"


ACard::ACard()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ACard::Construct(ABuildingsController* buildingsController)
{
	BuildingsController = buildingsController;
}

void ACard::BeginPlay()
{
	Super::BeginPlay();
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
	BuildingsController->CreateBuildingUnderScreenPosition(ScreenPosition, Building);
	
	OnCardAppliedDelegate.Broadcast(this);
}

