﻿#include "AEntityView.h"

AEntityView::AEntityView()
{
	PrimaryActorTick.bCanEverTick = true;
	
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	MainMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MainMesh"));
	MainMesh->SetupAttachment(RootComponent);
}

void AEntityView::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	GetComponents<UStaticMeshComponent>(MeshComponents);
}

TArray<UStaticMeshComponent*> AEntityView::GetMeshComponents() const
{
	return MeshComponents;
}
