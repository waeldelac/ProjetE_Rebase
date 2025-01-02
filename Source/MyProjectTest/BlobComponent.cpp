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
		NewPair.Value = 0;
		Composition.Add(NewPair);
	}


	

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

}

void UBlobComponent::InitializeBlobComposition(int32 EarthValue, int32 WaterValue, int32 FireValue, int32 AirValue)
{
	for (FBlobElement& Pair : Composition)
	{
		switch (Pair.Element)
		{
		case E_ELEMENT::EARTH:
			Pair.Value = EarthValue;
			break;
		case E_ELEMENT::WATER:
			Pair.Value = WaterValue;
			break;
		case E_ELEMENT::FIRE:
			Pair.Value = FireValue;
			break;
		case E_ELEMENT::AIR:
			Pair.Value = AirValue;
			break;
		default:
			break; // Pas d'action pour d'autres éléments (ou éléments non pris en charge)
		}
	}
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

E_ELEMENT UBlobComponent::getElementInInteraction()
{
	for (FBlobElement& CompositionItem : Composition)
	{
		if (CompositionItem.Value > 0)
		{
			return CompositionItem.Element;
		}
	}
	return E_ELEMENT::AIR;
}


/*
void UBlobComponent::addBlobInterraction(AActor* Actor)
{
	if (IBlobInterface* BlobInterface = Cast<IBlobInterface>(Actor))
	{
		UBlobComponent* TargetBlobComponent = BlobInterface->getBlobComponent();

		if (TargetBlobComponent && !OverlappingBlobs.Contains(TargetBlobComponent))
		{
			OverlappingBlobs.Add(TargetBlobComponent, E_INTERACTION_STATE::NotReady);
		}
	}
}


void UBlobComponent::removeBlobInterraction(AActor* Actor)
{
	UBlobComponent* TargetBlobComponent = Cast<IBlobInterface>(Actor)->getBlobComponent();
	if (TargetBlobComponent && !OverlappingBlobs.Contains(TargetBlobComponent))
	{
		OverlappingBlobs.Remove(TargetBlobComponent);
	}
}*/



