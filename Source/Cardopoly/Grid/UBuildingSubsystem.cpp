// Fill out your copyright notice in the Description page of Project Settings.
#include "UBuildingSubsystem.h"

#include "UGridSubsystem.h"
#include "Cardopoly/ABuilding.h"

void UBuildingSubsystem::PostInitialize()
{
	Super::PostInitialize();
	GridSubsystem = GetWorld()->GetSubsystem<UGridSubsystem>();
	UE_LOG(LogTemp, Warning, TEXT("%hs"), "Initialize UBuildingSubsystem");
}

void UBuildingSubsystem::CreateBuilding(const FVector Position) const
{
	FRotator SpawnRotation = FRotator::ZeroRotator;

	FVector CellPosition = GridSubsystem->GetClosestCellCenterWorldPosition(Position);
	
	FActorSpawnParameters SpawnParams;
	GetWorld()->SpawnActor<ABuilding>(ABuilding::StaticClass(), CellPosition, SpawnRotation, SpawnParams);
}
