#include "HandSystem.h"

#include "Cardopoly/Configs/HandLocalConfig.h"
#include "Cardopoly/Configs/Cards/BuildingCardDataRaw.h"
#include "Cardopoly/ECS/Core/Cards/Components/BuildingCardComponent.hpp"
#include "Cardopoly/ECS/Core/Cards/Components/CardAddedEvent.hpp"
#include "Cardopoly/ECS/Core/Cards/Components/CardComponent.hpp"
#include "Cardopoly/ECS/Core/Cards/Components/CardInHandRelation.hpp"
#include "Cardopoly/ECS/Core/Cards/Components/FDrawCardRequest.hpp"
#include "Cardopoly/ECS/Core/Player/Common/Components/PlayerIndexComponent.hpp"
#include "Cardopoly/ECS/Core/Player/Common/Components/PlayerTag.hpp"
#include "Kismet/KismetMathLibrary.h"

void HandSystem::Initialize()
{
	UHandLocalConfig* handLocalConfig = _localConfigHolder->HandLocalConfig;

	flecs::query<> filter = _world->query_builder()
		.with<PlayerTag>()
		.with<PlayerIndexComponent>()
		.build();

	_world->defer_begin();
	filter.each([this, handLocalConfig](flecs::entity entity) {
		for (int i = 0; i < handLocalConfig->CardsStartCount; ++i)
		{
			DrawCard(entity);
		}
	});
	_world->defer_end();

	filter.each([this, handLocalConfig](flecs::entity entity) {
		auto firstChild = _world->query_builder()
				.with(flecs::ChildOf,entity)
				.build()
			;

		firstChild.each([&](flecs::iter& it, size_t) {
				/*child.set<ApplyCardRequest>({});*/
			UE_LOG(LogTemp, Warning, TEXT("-----"));
		});	
	});
	
	
	_world->system<const FDrawCardRequest>("HandSystem")
		.with<PlayerIndexComponent>()
		.immediate()
		.write<CardAddedEvent>()
		.write<CardInHandRelation>()
		.write<CardComponent>()
		.write<BuildingCardComponent>()
		.write(flecs::ChildOf)
		.write<FDrawCardRequest>()
		.each([this](flecs::entity playerEntity, const FDrawCardRequest& request)
		{
			DrawCard(playerEntity);
		});
}

void HandSystem::DrawCard(flecs::entity playerEntity)
{
	const PlayerIndexComponent* playerIndexComponent = playerEntity.get<PlayerIndexComponent>();
	
	TArray<FName> RowNames = _cardConfigService->GetAllNames();
	int32 RandomIndex = UKismetMathLibrary::RandomInteger(RowNames.Num());
	FName cardId = RowNames[RandomIndex];
	
	flecs::entity cardEntity = _cardEntityFactory->Create(cardId);

	cardEntity.set<PlayerIndexComponent>({playerIndexComponent->Value});
	cardEntity.child_of(playerEntity);
	cardEntity.add<CardInHandRelation>(playerEntity);

	_world->entity()
		.set<CardAddedEvent>(
			{
				cardEntity,
				playerIndexComponent->Value
			}
		);

	playerEntity.remove<FDrawCardRequest>();
}
