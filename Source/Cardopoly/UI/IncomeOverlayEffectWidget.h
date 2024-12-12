#pragma once

#include "CoreMinimal.h"
#include "EntityOverlayWidget.h"
#include "IncomeOverlayEffectWidget.generated.h"


class FCTweenInstance;

UCLASS()
class CARDOPOLY_API UIncomeOverlayEffectWidget : public UEntityOverlayWidget
{
	GENERATED_BODY()
public:
	void Construct(int32 value);
	
	virtual void BeginDestroy() override;

	virtual void BeginAnimation() override;

private:
	UPROPERTY(meta = (BindWidget))
	class URichTextBlock* Text;

	FCTweenInstance* _tween = nullptr;
};
