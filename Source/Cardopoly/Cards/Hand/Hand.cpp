#include "Hand.h"

#include "Cardopoly/Cards/Card.h"
#include "Cardopoly/Cards/CardFactory.h"
#include "Cardopoly/EventBus/Events/CreateCardEvent.h"
#include "Cardopoly/EventBus/Events/DestroyCardEvent.h"

class EventBus;

AHand::AHand()
{
	auto Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;
	PrimaryActorTick.bCanEverTick = true;
}

void AHand::Construct(UCardFactory* cardFactory, EventBus* eventBus)
{
	m_cardFactory = cardFactory;
	m_eventBus = eventBus;
}

void AHand::BeginPlay()
{
	Super::BeginPlay();
}

void AHand::DrawCard()
{
	CardSlots.Add(FVector());

	ACard* Card = m_cardFactory->CreateCard();
	Cards.Add(Card);
	Card->OnCardAppliedDelegate.AddUniqueDynamic(this, &ThisClass::OnCardApplied);
	
	OnDrawCardDelegate.Broadcast(Card);
	m_eventBus->FireEvent(CreateCardEvent(Card));
}

TArray<ACard*> AHand::GetCards() const
{
	return Cards;
}

void AHand::OnCardApplied(ACard* Card)
{
	Cards.Remove(Card);
	m_eventBus->FireEvent(DestroyCardEvent(Card));
	Card->Destroy();
}
