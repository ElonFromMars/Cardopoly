#pragma once

#include "CoreMinimal.h"
#include "Properties/FlecsComponentProperties.h"
#include "FPositionComponent.generated.h"

USTRUCT(BlueprintType)
struct CARDOPOLY_API FPositionComponent final
{
	GENERATED_BODY()

	FORCEINLINE FPositionComponent() = default;
	FORCEINLINE FPositionComponent(float x, float y, float z) : X(x), Y(y), Z(z), TestField(0){}

	UPROPERTY()
	float X;

	UPROPERTY()
	float Y;

	UPROPERTY()
	float Z;

	UPROPERTY()
	int32 TestField = 0;
};

REGISTER_FLECS_COMPONENT_PROPERTIES(FPositionComponent, { flecs::Sparse }, {} )
