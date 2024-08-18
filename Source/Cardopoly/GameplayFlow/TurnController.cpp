#include "TurnController.h"

#include "Cardopoly/Cards/Hand/Hand.h"
#include "Cardopoly/Configs/HandLocalConfig.h"

ATurnController::ATurnController()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ATurnController::BeginPlay()
{
	Super::BeginPlay();
}

void ATurnController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATurnController::Construct(AHand* PlayerHand, UHandLocalConfig* PlayerHandLocalConfig)
{
	Hand = PlayerHand;
	HandLocalConfig = PlayerHandLocalConfig;
}

void ATurnController::StartSession()
{
	for (int i = 0; i < HandLocalConfig->CardsStartCount; ++i)
	{
		Hand->DrawCard();	
	}
}

void ATurnController::EndTurn(int PlayerIndex)
{
	Hand->DrawCard();
}



