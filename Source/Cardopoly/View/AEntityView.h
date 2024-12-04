#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AEntityView.generated.h"

UCLASS()
class CARDOPOLY_API AEntityView : public AActor
{
	GENERATED_BODY()

public:
	AEntityView();

	virtual void OnConstruction(const FTransform& Transform) override;

	virtual TArray<UStaticMeshComponent*> GetMeshComponents() const;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh")
	UStaticMeshComponent* MainMesh;

protected:
	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite, Category = "Mesh")
	TArray<UStaticMeshComponent*> MeshComponents;
};
