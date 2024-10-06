#pragma once

#include "CoreMinimal.h"
#include "IOccupyGrid.h"
#include "Components/ActorComponent.h"
#include "GridObjectComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CARDOPOLY_API UGridObjectComponent : public UActorComponent, public IOccupyGrid
{
	GENERATED_BODY()
	
	FIntVector m_position;
	
public:
	UPROPERTY(EditDefaultsOnly)
	FIntVector SquareSize;
	
	void SetPosition(FIntVector position);
	
	virtual FIntVector GetPosition() override;

	virtual IOccupyGridData* GetGridData() override;
};
