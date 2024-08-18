#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TurnController.generated.h"

class UHandLocalConfig;
class AHand;

UCLASS()
class CARDOPOLY_API ATurnController : public AActor
{
	GENERATED_BODY()

private:
	AHand* Hand;
	UHandLocalConfig* HandLocalConfig;

public:
	ATurnController();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	void Construct(AHand* PlayerHand, UHandLocalConfig* PlayerHandLocalConfig);
	void StartSession();

	UFUNCTION(BlueprintCallable)
	void EndTurn(int PlayerIndex);
};
