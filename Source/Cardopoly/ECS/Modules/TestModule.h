#pragma once

#include "CoreMinimal.h"
#include "Modules/FlecsModuleInterface.h"
#include "Modules/FlecsModuleProgressInterface.h"
#include "Systems/FlecsSystem.h"
#include "UObject/Object.h"
#include "TestModule.generated.h"

UCLASS(Blueprintable, BlueprintType, EditInlineNew)
class CARDOPOLY_API UTestModule final : public UObject, public IFlecsModuleInterface, public IFlecsModuleProgressInterface
{
	GENERATED_BODY()

public:
	UTestModule(const FObjectInitializer& InObjectInitializer);

	virtual void InitializeModule(UFlecsWorld* InWorld, const FFlecsEntityHandle& InModuleEntity) override;
	virtual void DeinitializeModule(UFlecsWorld* InWorld) override;

	FORCEINLINE virtual void ProgressModule(double InDeltaTime) override;

	FORCEINLINE virtual FString GetModuleName_Implementation() const override { return TEXT("Flecs Test Module"); }
}; // class UFlecsTickerModule

