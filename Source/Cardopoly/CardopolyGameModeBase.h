#pragma once

#include "CoreMinimal.h"
#include "Configs/UCityGeneratorConfig.h"
#include "GameFramework/GameModeBase.h"
#include "CardopolyGameModeBase.generated.h"

class ULocalConfigHolder;
class AHand;
class UGameplayAssetData;

UCLASS()
class CARDOPOLY_API ACardopolyGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Configs")
	UCityGeneratorConfig* CityGeneratorConfig;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Configs")
	ULocalConfigHolder* LocalConfigHolder;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AssetData")
	UGameplayAssetData* GameplayAssetData;
	
	ACardopolyGameModeBase();

	virtual void BeginPlay() override;

	void CreateCity() const;
	void CreateHand() const;
	void CreateInput() const;
};
