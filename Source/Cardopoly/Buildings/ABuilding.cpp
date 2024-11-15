#include "ABuilding.h"
#include "Components/SphereComponent.h"

ABuilding::ABuilding()
{
	// Set this actor to call Tick() every frame
	PrimaryActorTick.bCanEverTick = true;

	// Create the sphere mesh component
	SphereMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SphereMesh"));
	RootComponent = SphereMesh;

	// Set the sphere mesh
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereMeshAsset(TEXT("/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube"));
	if (SphereMeshAsset.Succeeded())
	{
		SphereMesh->SetStaticMesh(SphereMeshAsset.Object);
	}
}
