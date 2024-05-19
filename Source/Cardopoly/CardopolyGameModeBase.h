#pragma once

#include "CoreMinimal.h"
#include "Configs/UCityGeneratorConfig.h"
#include "GameFramework/GameModeBase.h"
#include "CardopolyGameModeBase.generated.h"

UCLASS()
class CARDOPOLY_API ACardopolyGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Configs")
	UCityGeneratorConfig* cityGeneratorConfig;
	
	ACardopolyGameModeBase();

	virtual void BeginPlay() override;

	void CreateCity();
};
