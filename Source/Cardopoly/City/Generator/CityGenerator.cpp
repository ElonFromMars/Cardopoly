#include "CityGenerator.h"
#include "Cardopoly/Buildings/BuildingsController.h"
#include "Cardopoly/Configs/UCityGeneratorConfig.h"

void CityGenerator::Generate()
{
	for (int x = 0; x < CityGeneratorConfig->GridSizeY; ++x)
	{
		for (int y = 0; y < CityGeneratorConfig->GridSizeX; ++y)
		{
			if(FMath::FRand() > CityGeneratorConfig->HouseProbability) continue;
			
			FIntVector SpawnLocation = FIntVector(x, y, 0);
			BuildingsController->CreateBuilding(SpawnLocation, 0);
		}	
	}
}
