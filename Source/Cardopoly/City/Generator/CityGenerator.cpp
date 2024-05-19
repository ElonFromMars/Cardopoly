#include "CityGenerator.h"

#include "Cardopoly/ABuilding.h"
#include "Cardopoly/City/ACity.h"
#include "Cardopoly/Configs/UCityGeneratorConfig.h"

void CityGenerator::Generate()
{
	FActorSpawnParameters spawnParams;
	world->SpawnActor<ACity>(ACity::StaticClass());
	
	for (int x = 0; x < cityGeneratorConfig->GridSizeY; ++x)
	{
		for (int y = 0; y < cityGeneratorConfig->GridSizeX; ++y)
		{
			if(FMath::FRand() > cityGeneratorConfig->HouseProbability) continue;
			
			FRotator SpawnRotation(FRotator::ZeroRotator);
			const float CellSize = cityGeneratorConfig->CellSize;
			FVector SpawnLocation = FVector(x * CellSize, y * CellSize,0); 
			
			FActorSpawnParameters SpawnParams;
			world->SpawnActor<ABuilding>(ABuilding::StaticClass(), SpawnLocation, SpawnRotation, SpawnParams);
		}	
	}
}
