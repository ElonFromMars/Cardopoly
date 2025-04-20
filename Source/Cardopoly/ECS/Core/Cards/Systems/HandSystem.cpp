#include "HandSystem.h"

#include "Cardopoly/Configs/HandLocalConfig.h"
#include "Cardopoly/Configs/Cards/BuildingCardDataRaw.h"
#include "Cardopoly/ECS/Core/Cards/Components/CardAddedEvent.hpp"
#include "Cardopoly/ECS/Core/Cards/Components/CardComponent.hpp"
#include "Cardopoly/ECS/Core/Cards/Components/CardsRelation.hpp"
#include "Cardopoly/ECS/Core/Cards/Components/FDrawCardRequest.hpp"
#include "Cardopoly/ECS/Core/Player/Common/Components/PlayerIndexComponent.hpp"
#include "Cardopoly/ECS/Core/Player/Common/Components/PlayerTag.hpp"
#include "Kismet/KismetMathLibrary.h"

void HandSystem::Initialize()
{
	UHandLocalConfig* handLocalConfig = _localConfigHolder->HandLocalConfig;

	_world->each<PlayerTag>([handLocalConfig, this](flecs::entity entity, const PlayerTag playerTag) {
		for (int i = 0; i < handLocalConfig->CardsStartCount; ++i)
		{
			DrawCard(entity);
		}
	});
	
	_world->system<const FDrawCardRequest>("HandSystem")
		.immediate()
		.write<CardAddedEvent>()
		.write<CardsRelation>()
		.write<CardComponent>()
		.each([this](flecs::entity playerEntity, const FDrawCardRequest& request)
		{
			DrawCard(playerEntity);
		});
}

void HandSystem::DrawCard(flecs::entity playerEntity)
{
	UDataTable* buildingCardsConfig = _localConfigHolder->BuildingCardsConfig;
			
	TArray<FName> RowNames = buildingCardsConfig->GetRowNames();
	int32 RandomIndex = UKismetMathLibrary::RandomInteger(RowNames.Num());
	FName cardId = RowNames[RandomIndex];
			
	FString ContextString = "houses query";
	FBuildingCardDataRaw* CardData = buildingCardsConfig->FindRow<FBuildingCardDataRaw>(cardId, ContextString);
			
	static_cast<uint32>(CardData->BuildingId);

	flecs::entity cardEntity = _world->entity()
		.set<CardComponent>({cardId});
	
	playerEntity.add<CardsRelation>(cardEntity);


	_world->entity()
		.set<CardAddedEvent>(
			{
				cardEntity,
				playerEntity.get<PlayerIndexComponent>()->Value
			}
		);

	playerEntity.remove<FDrawCardRequest>();
}
