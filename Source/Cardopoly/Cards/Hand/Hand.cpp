#include "Hand.h"

#include "Cardopoly/Cards/Card.h"
#include "Cardopoly/Cards/CardFactory.h"

AHand::AHand()
{
	auto Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;
	PrimaryActorTick.bCanEverTick = true;
}

void AHand::Init(UCardFactory* cardFactory)
{
	this->CardFactory = cardFactory;
}

void AHand::BeginPlay()
{
	Super::BeginPlay();
}

void AHand::DrawCard()
{
	CardSlots.Add(FVector());
	UpdateSlotPositions();

	ACard* Card = CardFactory->CreateCard();
	Card->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
	Card->SetActorRelativeLocation(CardSlots[0]);
}

void AHand::UpdateSlotPositions()
{
	float leftX;
	if (CardSlots.Num() > 1)
	{
		leftX = -((CardSlots.Num() - 1) / 2.0) * DistanceBetweenCards;
	}
	else
	{
		leftX = 0;
	}

	const FVector LeftPosition = FVector(BottomCenterPosition.X + leftX, BottomCenterPosition.Y, BottomCenterPosition.Z);
	FVector cardPosition = LeftPosition;
	for (int i = 0; i < CardSlots.Num(); ++i)
	{
		FVector& CardSlotsIt = CardSlots[i];

		CardSlotsIt = cardPosition;
            
		cardPosition += FVector(DistanceBetweenCards, 0, 0);
	}
}
