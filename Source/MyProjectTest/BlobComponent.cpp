// Fill out your copyright notice in the Description page of Project Settings.


#include "BlobComponent.h"



// Sets default values for this component's properties
UBlobComponent::UBlobComponent()
{
	//placebo = NewObject<UElement>();
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	
	for (int32 ElementIndex = 0; ElementIndex < static_cast<int32>(E_ELEMENT::ETHER) + 1; ++ElementIndex)
	{
		FBlobElement NewPair;
		NewPair.Element = static_cast<E_ELEMENT>(ElementIndex);
		NewPair.Value = 100;
		Composition.Add(NewPair);
	}


	EarthInterraction = CreateDefaultSubobject<UElementTargetInteraction>(TEXT("EarthInteraction"));
	//Defining Earth interraction 
	EarthInterraction->ElementInterraction.Add(E_ELEMENT::EARTH, E_INTERRACTION_TYPE::COLLISION);
	EarthInterraction->ElementInterraction.Add(E_ELEMENT::WATER, E_INTERRACTION_TYPE::NOTHING_HAPPEN);
	EarthInterraction->ElementInterraction.Add(E_ELEMENT::FIRE, E_INTERRACTION_TYPE::TRANSFERT_TO_NEXT_ELEM);
	EarthInterraction->ElementInterraction.Add(E_ELEMENT::AIR, E_INTERRACTION_TYPE::DESTROY);
	InterractionMapping.Add(E_ELEMENT::EARTH, EarthInterraction);


	//Defining Water interraction 
	WaterInterraction = CreateDefaultSubobject<UElementTargetInteraction>(TEXT("WaterInteraction"));
	WaterInterraction->ElementInterraction.Add(E_ELEMENT::EARTH, E_INTERRACTION_TYPE::NOTHING_HAPPEN);
	WaterInterraction->ElementInterraction.Add(E_ELEMENT::WATER, E_INTERRACTION_TYPE::NOTHING_HAPPEN);
	WaterInterraction->ElementInterraction.Add(E_ELEMENT::FIRE, E_INTERRACTION_TYPE::GAIN);
	WaterInterraction->ElementInterraction.Add(E_ELEMENT::AIR, E_INTERRACTION_TYPE::NOTHING_HAPPEN);//Glace ?
	InterractionMapping.Add(E_ELEMENT::WATER, WaterInterraction);


	//Defining Fire interraction 
	FireInterraction = CreateDefaultSubobject<UElementTargetInteraction>(TEXT("FireInteraction"));
	FireInterraction->ElementInterraction.Add(E_ELEMENT::EARTH, E_INTERRACTION_TYPE::TRANSFERT_TO_NEXT_ELEM);
	FireInterraction->ElementInterraction.Add(E_ELEMENT::WATER, E_INTERRACTION_TYPE::DESTROY);
	FireInterraction->ElementInterraction.Add(E_ELEMENT::FIRE, E_INTERRACTION_TYPE::NOTHING_HAPPEN);
	FireInterraction->ElementInterraction.Add(E_ELEMENT::AIR, E_INTERRACTION_TYPE::GAIN);
	InterractionMapping.Add(E_ELEMENT::FIRE, FireInterraction);


	//Defining Air interraction 
	AirInterraction = CreateDefaultSubobject<UElementTargetInteraction>(TEXT("AirInteraction"));
	AirInterraction->ElementInterraction.Add(E_ELEMENT::EARTH, E_INTERRACTION_TYPE::NOTHING_HAPPEN);
	AirInterraction->ElementInterraction.Add(E_ELEMENT::WATER, E_INTERRACTION_TYPE::NOTHING_HAPPEN);
	AirInterraction->ElementInterraction.Add(E_ELEMENT::FIRE, E_INTERRACTION_TYPE::DESTROY);
	AirInterraction->ElementInterraction.Add(E_ELEMENT::AIR, E_INTERRACTION_TYPE::NOTHING_HAPPEN);//Foudre? 
	InterractionMapping.Add(E_ELEMENT::AIR, AirInterraction);

}

void UBlobComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME_CONDITION(UBlobComponent, Composition, COND_None);
}

// Called when the game starts
void UBlobComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UBlobComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	for (auto TargetBlobComponent : BlobListInInterraction)
	{
		if (TargetBlobComponent != NULL)
		{
			manageOnHitInteraction(TargetBlobComponent);
		}
	}
	

	// ...
}

void UBlobComponent::interractElement()
{

}

int UBlobComponent::getElemValue(E_ELEMENT element)
{
	int val = 0;
	
	for (FBlobElement& Pair : Composition)
	{
		if (Pair.Element == element)
		{
			val = Pair.Value;
			break; // Sortir de la boucle une fois que la paire a été mise à jour
		}
	}
	return val;
	
	
}

int UBlobComponent::setElemValue(E_ELEMENT element,int value)
{
	int ret = -1;

	for (FBlobElement& Pair : Composition)
	{
		if (Pair.Element == element && Pair.Authorization != E_MAPPED_AUTHORIZATION::NOTHING_ALLOWED && Pair.Playability !=  E_PLAYABLE::LOCKED && Pair.Playability != E_PLAYABLE::INFINITE)
		{
			Pair.Value = value;
			ret = 0;
			break; // Sortir de la boucle une fois que la paire a été mise à jour
		}
	}
	return 0;


}

int UBlobComponent::incrementElemValue(int value, E_ELEMENT element) {

	int ret = -1;

	for (FBlobElement& Pair : Composition)
	{
		if (Pair.Element == element && Pair.Authorization !=  E_MAPPED_AUTHORIZATION::INCREMENT_MANDATORY && Pair.Playability != E_PLAYABLE::LOCKED)
		{
			if(Pair.Playability != E_PLAYABLE::ABSORB && Pair.Playability != E_PLAYABLE::INFINITE)
				Pair.Value += value;
			ret = 0;
			break; // Sortir de la boucle une fois que la paire a été mise à jour
		}
	}
	return ret;
}

int UBlobComponent::decrementElemValue(int value, E_ELEMENT element ) {

	int ret = -1;

	for (FBlobElement& Pair : Composition )
	{
		if (Pair.Element == element && Pair.Authorization != E_MAPPED_AUTHORIZATION::DECREMENT_MANDATORY && Pair.Playability != E_PLAYABLE::LOCKED)
		{
			if (Pair.Playability != E_PLAYABLE::INFINITE)
				Pair.Value -= value;
			ret = 0;
			break; // Sortir de la boucle une fois que la paire a été mise à jour
		}
	}
	return 0;
}

int UBlobComponent::chooseAction(E_ELEMENT	TargetElement, E_PLAYABLE	playability) {

	for (FBlobElement& StructElem : Composition)
	{
		if (StructElem.Element == TargetElement)
		{
			StructElem.Playability = playability;
			break; // Sortir de la boucle une fois que la paire a été mise à jour
		}
	}
	return 0;
}

void UBlobComponent::setElementConfig(E_ELEMENT element, E_PLAYABLE	playability, E_MAPPED_AUTHORIZATION  Authorization, int Value) {
	for (FBlobElement& Pair : Composition)
	{
		if (Pair.Element == element)
		{
			Pair.Playability = playability;
			Pair.Authorization = Authorization;
			Pair.Value = Value;
			break; // Sortir de la boucle une fois que la paire a été mise à jour
		}
	}
}

void UBlobComponent::manageOnHitInteraction(UBlobComponent* TargetBlobComponent) {
	for (FBlobElement& myComposition : Composition)
	{
		if (myComposition.Value > 0)
		{
			for (FBlobElement& TargetComposition : TargetBlobComponent->Composition)
			{
				if (TargetComposition.Value > 0)
				{
					E_INTERRACTION_TYPE interractionToApply = determineInteraction(myComposition.Element, TargetComposition.Element);
					//If interact for the current blob1 element must stop -> break the loop
					bool shouldBreak = false;
					switch (interractionToApply)
					{
					case E_INTERRACTION_TYPE::COLLISION:
						shouldBreak = true;
						break;
					case E_INTERRACTION_TYPE::TRANSFERT_TO_NEXT_ELEM:
						break;
					case E_INTERRACTION_TYPE::NOTHING_HAPPEN:
						shouldBreak = true;
						break;
					case E_INTERRACTION_TYPE::DESTROY:
						decrementElemValue(1, myComposition.Element);
						shouldBreak = true;
						break;
					case E_INTERRACTION_TYPE::GAIN:
						shouldBreak = true;
						break;
					default:
						break;
					}
				}
			}
		}
	}
}

E_INTERRACTION_TYPE UBlobComponent::determineInteraction(E_ELEMENT elementBlob1, E_ELEMENT elementBlob2) {

	return *(**InterractionMapping.Find(elementBlob1)).ElementInterraction.Find(elementBlob2);

}

