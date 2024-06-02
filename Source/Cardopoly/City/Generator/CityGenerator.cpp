#include "CityGenerator.h"

#include "Cardopoly/ABuilding.h"
#include "Cardopoly/City/ACity.h"
#include "Cardopoly/Configs/UCityGeneratorConfig.h"
#include "Cardopoly/Grid/UGridSubsystem.h"

void CityGenerator::Generate()
{
	FActorSpawnParameters spawnParams;
	world->SpawnActor<ACity>(ACity::StaticClass());
	UGridSubsystem* GridSubsystem = world->GetSubsystem<UGridSubsystem>();
	
	for (int x = 0; x < cityGeneratorConfig->GridSizeY; ++x)
	{
		for (int y = 0; y < cityGeneratorConfig->GridSizeX; ++y)
		{
			if(FMath::FRand() > cityGeneratorConfig->HouseProbability) continue;
			
			FRotator SpawnRotation(FRotator::ZeroRotator);
			FVector SpawnLocation = GridSubsystem->GetCellCenterWorldPosition(x, y);; 
			
			FActorSpawnParameters SpawnParams;
			world->SpawnActor<ABuilding>(ABuilding::StaticClass(), SpawnLocation, SpawnRotation, SpawnParams);
		}	
	}
}
