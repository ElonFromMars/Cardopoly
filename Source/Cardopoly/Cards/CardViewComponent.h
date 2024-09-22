#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CardViewComponent.generated.h"


class UCardWidget;
class UTextRenderComponent;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CARDOPOLY_API UCardViewComponent : public USceneComponent
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, Category = "Text")
	UCardWidget* Widget;
	
public:
	UCardViewComponent();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SetDescriptionText(const FText& Value) const;
	void SetNameText(const FText& Value) const;
	void SetCostText(const FText& Value) const;
};
