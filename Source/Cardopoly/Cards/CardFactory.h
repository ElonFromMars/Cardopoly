#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "CardFactory.generated.h"

class ACard;

UCLASS()
class CARDOPOLY_API UCardFactory : public UObject
{
	GENERATED_BODY()

public:
	virtual void Init();
	virtual ACard* CreateCard();
};
