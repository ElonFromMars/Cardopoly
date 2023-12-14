#include "ABuildingActor.h"
#include "Components/SphereComponent.h"

ABuildingActor::ABuildingActor()
{
	// Set this actor to call Tick() every frame
	PrimaryActorTick.bCanEverTick = true;

	// Create the sphere mesh component
	SphereMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SphereMesh"));
	RootComponent = SphereMesh;

	// Set the sphere mesh
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereMeshAsset(TEXT("/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere"));
	if (SphereMeshAsset.Succeeded())
	{
		SphereMesh->SetStaticMesh(SphereMeshAsset.Object);
	}
}

void ABuildingActor::BeginPlay()
{
	Super::BeginPlay();
}

void ABuildingActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
