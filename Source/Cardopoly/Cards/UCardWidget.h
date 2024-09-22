#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UCardWidget.generated.h"


UCLASS()
class CARDOPOLY_API UCardWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "Card")
	void SetName(const FText Name);

	UFUNCTION(BlueprintCallable, Category = "Card")
	void SetDescription(const FText Description);
	UFUNCTION(BlueprintCallable, Category = "Card")
	void SetCost(const FText& Text);

protected:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* CardNameText;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* CardDescriptionText;
};
