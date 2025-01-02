// Fill out your copyright notice in the Description page of Project Settings.


#include "BlobInteractionManager.h"

UBlobInteractionManager::UBlobInteractionManager()
{
    InteractionMatrix[static_cast<int32>(E_ELEMENT::EARTH)][static_cast<int32>(E_ELEMENT::EARTH)] = E_INTERRACTION_TYPE::COLLISION;
    InteractionMatrix[static_cast<int32>(E_ELEMENT::EARTH)][static_cast<int32>(E_ELEMENT::WATER)] = E_INTERRACTION_TYPE::NOTHING_HAPPEN;
    InteractionMatrix[static_cast<int32>(E_ELEMENT::EARTH)][static_cast<int32>(E_ELEMENT::FIRE)] = E_INTERRACTION_TYPE::TRANSFERT_TO_NEXT_ELEM;
    InteractionMatrix[static_cast<int32>(E_ELEMENT::EARTH)][static_cast<int32>(E_ELEMENT::AIR)] = E_INTERRACTION_TYPE::DESTROY;

    InteractionMatrix[static_cast<int32>(E_ELEMENT::WATER)][static_cast<int32>(E_ELEMENT::EARTH)] = E_INTERRACTION_TYPE::NOTHING_HAPPEN;
    InteractionMatrix[static_cast<int32>(E_ELEMENT::WATER)][static_cast<int32>(E_ELEMENT::WATER)] = E_INTERRACTION_TYPE::NOTHING_HAPPEN;
    InteractionMatrix[static_cast<int32>(E_ELEMENT::WATER)][static_cast<int32>(E_ELEMENT::FIRE)] = E_INTERRACTION_TYPE::AIR_TRANSFORMATION;
    InteractionMatrix[static_cast<int32>(E_ELEMENT::WATER)][static_cast<int32>(E_ELEMENT::AIR)] = E_INTERRACTION_TYPE::ICE_GENERATION;

    InteractionMatrix[static_cast<int32>(E_ELEMENT::FIRE)][static_cast<int32>(E_ELEMENT::EARTH)] = E_INTERRACTION_TYPE::TRANSFERT_TO_NEXT_ELEM;
    InteractionMatrix[static_cast<int32>(E_ELEMENT::FIRE)][static_cast<int32>(E_ELEMENT::WATER)] = E_INTERRACTION_TYPE::DESTROY;
    InteractionMatrix[static_cast<int32>(E_ELEMENT::FIRE)][static_cast<int32>(E_ELEMENT::FIRE)] = E_INTERRACTION_TYPE::NOTHING_HAPPEN;
    InteractionMatrix[static_cast<int32>(E_ELEMENT::FIRE)][static_cast<int32>(E_ELEMENT::AIR)] = E_INTERRACTION_TYPE::INCREMENTATION;

    InteractionMatrix[static_cast<int32>(E_ELEMENT::AIR)][static_cast<int32>(E_ELEMENT::EARTH)] = E_INTERRACTION_TYPE::NOTHING_HAPPEN;
    InteractionMatrix[static_cast<int32>(E_ELEMENT::AIR)][static_cast<int32>(E_ELEMENT::WATER)] = E_INTERRACTION_TYPE::NOTHING_HAPPEN;
    InteractionMatrix[static_cast<int32>(E_ELEMENT::AIR)][static_cast<int32>(E_ELEMENT::FIRE)] = E_INTERRACTION_TYPE::DESTROY;
    InteractionMatrix[static_cast<int32>(E_ELEMENT::AIR)][static_cast<int32>(E_ELEMENT::AIR)] = E_INTERRACTION_TYPE::THUNDER_GENERATION;
}

void UBlobInteractionManager::RegisterInteraction(AActor* ActorA, AActor* ActorB)
{
	IBlobInterface* BlobA = Cast<IBlobInterface>(ActorA);
	IBlobInterface* BlobB = Cast<IBlobInterface>(ActorB);

    if (!BlobA || !BlobB || BlobA == BlobB)
    {
        return; // Évite les problèmes avec des références nulles ou identiques
    }

    ActiveInteractions.Add(TPair<UBlobComponent*, UBlobComponent*>(BlobA->getBlobComponent(), BlobB->getBlobComponent()));
}

void UBlobInteractionManager::UnregisterInteraction(AActor* ActorA, AActor* ActorB)
{
	IBlobInterface* BlobA = Cast<IBlobInterface>(ActorA);
	IBlobInterface* BlobB = Cast<IBlobInterface>(ActorB);
    ActiveInteractions.Remove(TPair<UBlobComponent*, UBlobComponent*>(BlobA->getBlobComponent(), BlobB->getBlobComponent()));
}

bool UBlobInteractionManager::AreBlobsInteracting(UBlobComponent* BlobA, UBlobComponent* BlobB) const
{
    return ActiveInteractions.Contains(TPair<UBlobComponent*, UBlobComponent*>(BlobA, BlobB));
}

void UBlobInteractionManager::UpdateInteractions(float DeltaTime)
{
    for (const TPair<UBlobComponent*, UBlobComponent*>& Interaction : ActiveInteractions)
    {
        UBlobComponent* BlobA = Interaction.Key;
        UBlobComponent* BlobB = Interaction.Value;
		E_ELEMENT ElemInteractionBlobA;
		E_ELEMENT ElemInteractionBlobB;

        if (BlobA && BlobB)
        {
			E_INTERRACTION_TYPE InterractionAToB = determineInteraction(BlobA, BlobB, &ElemInteractionBlobA);
			E_INTERRACTION_TYPE InterractionBToA = determineInteraction(BlobB, BlobA, &ElemInteractionBlobB);
			ApplyInteractionOn(BlobA, InterractionAToB, ElemInteractionBlobA, DeltaTime);
			ApplyInteractionOn(BlobB, InterractionBToA, ElemInteractionBlobB, DeltaTime);

        }
    }
}

E_INTERRACTION_TYPE UBlobInteractionManager::determineInteraction(UBlobComponent* BlobA, UBlobComponent* BlobB, E_ELEMENT* InteractionElement)
{
	for (FBlobElement& CompositionA : BlobA->Composition)
	{
		if (CompositionA.Value > 0)
		{
			for (FBlobElement& CompositionB : BlobB->Composition)
			{
				if (CompositionB.Value > 0)
				{
					E_INTERRACTION_TYPE interractionToApply = InteractionMatrix[static_cast<int32>(CompositionA.Element)][static_cast<int32>(CompositionB.Element)];;
					//If interact for the current blob1 element must stop -> break the loop

					if (interractionToApply != E_INTERRACTION_TYPE::TRANSFERT_TO_NEXT_ELEM)
					{
						*InteractionElement = CompositionA.Element;
						return interractionToApply;
					}
				}
			}
		}
	}
	return E_INTERRACTION_TYPE::NOTHING_HAPPEN;

}

void UBlobInteractionManager::ApplyInteractionOn(UBlobComponent* Blob, E_INTERRACTION_TYPE Interaction, E_ELEMENT Element, float DeltaTime)
{
	switch (Interaction)
	{
	case E_INTERRACTION_TYPE::DESTROY:
		Blob->decrementElemValue(1, Element);
		return;
	case E_INTERRACTION_TYPE::AIR_TRANSFORMATION:
		Blob->incrementElemValue(1, E_ELEMENT::AIR);
		Blob->decrementElemValue(1, Element);
		return;
	case E_INTERRACTION_TYPE::INCREMENTATION:
		Blob->incrementElemValue(1, Element);
		return;
	case E_INTERRACTION_TYPE::DECREMENTATION:
		Blob->decrementElemValue(1, Element);
		return;
	default:
		break;
	}
}



