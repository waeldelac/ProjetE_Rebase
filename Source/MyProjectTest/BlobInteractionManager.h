#pragma once

#include "CoreMinimal.h"
#include "BlobComponent.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "BlobInteractionManager.generated.h"

UENUM()
enum class E_INTERRACTION_TYPE : uint8
{
    COLLISION = 0,
    TRANSFERT_TO_NEXT_ELEM,
    NOTHING_HAPPEN,
    DESTROY,
    AIR_TRANSFORMATION,
    INCREMENTATION,
    DECREMENTATION,
    ICE_GENERATION,
    THUNDER_GENERATION
};

/**
 * Manager des interactions entre blobs.
 */
UCLASS(Blueprintable)
class MYPROJECTTEST_API UBlobInteractionManager : public UGameInstanceSubsystem
{
    GENERATED_BODY()

private:
    // Liste des paires de blobs en interaction

    TSet<TPair<UBlobComponent*, UBlobComponent*>> ActiveInteractions;

public:

    E_INTERRACTION_TYPE InteractionMatrix[static_cast<int32>(4)][static_cast<int32>(4)];

    UBlobInteractionManager();

    // Ajouter une interaction entre deux blobs
    UFUNCTION(BlueprintCallable, Category = "Blob Interaction")
    void RegisterInteraction(AActor* ActorA, AActor* ActorB);

    // Supprimer une interaction entre deux blobs
    UFUNCTION(BlueprintCallable, Category = "Blob Interaction")
    void UnregisterInteraction(AActor* ActorA, AActor* ActorB);

    // Mettre à jour toutes les interactions
    UFUNCTION(BlueprintCallable, Category = "Blob Interaction")
    void UpdateInteractions(float DeltaTime);

    E_INTERRACTION_TYPE determineInteraction(UBlobComponent* BlobA, UBlobComponent* BlobB, E_ELEMENT* InteractionElement);

    // Vérifie si deux blobs sont déjà en interaction
    UFUNCTION(BlueprintPure, Category = "Blob Interaction")
    bool AreBlobsInteracting(UBlobComponent* BlobA, UBlobComponent* BlobB) const;

    void ApplyInteractionOn(UBlobComponent* Blob, E_INTERRACTION_TYPE Interaction, E_ELEMENT Element, float DeltaTime);
};
