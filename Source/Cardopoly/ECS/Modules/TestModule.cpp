#include "TestModule.h"

#include "Cardopoly/ECS/FPositionComponent.h"
#include "Worlds/FlecsWorld.h"


UTestModule::UTestModule(const FObjectInitializer& InObjectInitializer)
	: Super(InObjectInitializer)
{
}

void UTestModule::InitializeModule(UFlecsWorld* InWorld, const FFlecsEntityHandle& InModuleEntity)
{
	InWorld->EnableType<FPositionComponent>();
	
	InWorld->CreateSystemWithBuilder<FPositionComponent>(TEXT("TestSystem"))
		.kind(flecs::OnUpdate)
		.each([](FPositionComponent& pos) {
				pos.X += FMath::RandRange(-1.0f, 1.0f);
				pos.Y += FMath::RandRange(-1.0f, 1.0f);
				pos.Z += FMath::RandRange(-1.0f, 1.0f);
		});

	InWorld->CreateSystemWithBuilder<FPositionComponent>(TEXT("TestSystem2"))
		.kind(flecs::OnUpdate)
		.each([this](FPositionComponent& pos) {
		    DrawDebugPoint(GetWorld(), FVector(pos.X, pos.Y, pos.Z), 10.0f, FColor::Red, true, 0.1f);
		});
}

void UTestModule::DeinitializeModule(UFlecsWorld* InWorld)
{
	
}

void UTestModule::ProgressModule(double InDeltaTime)
{
}
