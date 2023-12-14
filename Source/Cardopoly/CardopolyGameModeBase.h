#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "CardopolyGameModeBase.generated.h"

UCLASS()
class CARDOPOLY_API ACardopolyGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	ACardopolyGameModeBase();

	virtual void BeginPlay() override;
};
