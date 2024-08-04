// Fill out your copyright notice in the Description page of Project Settings.
#include "UBuildingSubsystem.h"

#include "UGridSubsystem.h"
#include "Cardopoly/Buildings/ABuilding.h"

void UBuildingSubsystem::PostInitialize()
{
	Super::PostInitialize();
	GridSubsystem = GetWorld()->GetSubsystem<UGridSubsystem>();
	UE_LOG(LogTemp, Warning, TEXT("%hs"), "Initialize UBuildingSubsystem");
}

void UBuildingSubsystem::CreateBuildingUnderMouse()
{
	if(APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
	{
		FVector RayStart;
		FVector RayDirection;
		PlayerController->DeprojectMousePositionToWorld(RayStart, RayDirection); 
		RayDirection.Normalize();
		FVector RayEnd = RayStart + RayDirection * 10000.0f; 

		FHitResult HitResult;
		FCollisionQueryParams CollisionParams;

		UWorld* World = GetWorld();
		if (World->LineTraceSingleByChannel(HitResult, RayStart, RayEnd, ECC_GameTraceChannel1, CollisionParams))
		{
			CreateBuilding(HitResult.Location);
		}
	}
}

void UBuildingSubsystem::CreateBuilding(const FVector Position) const
{
	FRotator SpawnRotation = FRotator::ZeroRotator;

	FVector CellPosition = GridSubsystem->GetClosestCellCenterWorldPosition(Position);
	
	FActorSpawnParameters SpawnParams;
	GetWorld()->SpawnActor<ABuilding>(ABuilding::StaticClass(), CellPosition, SpawnRotation, SpawnParams);
}
