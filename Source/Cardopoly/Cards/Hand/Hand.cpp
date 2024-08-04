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

	ACard* Card = CardFactory->CreateCard();
	Cards.Add(Card);
	Card->OnCardAppliedDelegate.AddUniqueDynamic(this, &ThisClass::OnCardApplied);
	
	OnDrawCardDelegate.Broadcast(Card);
}

TArray<ACard*> AHand::GetCards() const
{
	return Cards;
}

void AHand::OnCardApplied(ACard* Card)
{
	Cards.Remove(Card);
	Card->Destroy();
}
