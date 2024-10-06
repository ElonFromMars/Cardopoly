#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "Worlds/FlecsWorldStartComponent.h"
#include "CardopolyGameState.generated.h"

UCLASS()
class CARDOPOLY_API ACardopolyGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	ACardopolyGameState();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
};
