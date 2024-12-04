#include "PositionConversionService.h"

#include "GridLayout.h"
#include "Cardopoly/Collision/CollisionConfig.h"
#include "Kismet/GameplayStatics.h"

bool PositionConversionService::ScreenPointToGroundPosition(const FVector2D screenPosition, FIntVector& cellPosition) const
{
	if(APlayerController* PlayerController = _viewWorld->GetFirstPlayerController())
	{
		FVector RayStart;
		FVector RayDirection;

		UGameplayStatics::DeprojectScreenToWorld(PlayerController, screenPosition, RayStart, RayDirection);
		
		RayDirection.Normalize();
		FVector RayEnd = RayStart + RayDirection * 10000.0f; 

		FHitResult HitResult;
		FCollisionQueryParams CollisionParams;
		
		if (_viewWorld->LineTraceSingleByChannel(HitResult, RayStart, RayEnd, ECC_GROUND, CollisionParams))
		{
			cellPosition = _gridLayout->WorldPositionToGrid(HitResult.Location);
			return true;
		}
	}
	return false;
}
