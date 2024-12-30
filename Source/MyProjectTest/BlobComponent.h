// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Net/UnrealNetwork.h"
#include "Element.h"
#include "BlobInterface.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BlobComponent.generated.h"




UENUM()
enum class E_PLAYABLE : uint8
{
	NORMAL = 0,
	LOCKED, //possede ou pas la resource mais ne permet pas d'en prendre
	INFINITE, //possede une infinite donc ne decremente pas
	ABSORB,
	TICK,//loot meme apres le click est fini
};

UENUM()
enum class E_MAPPED_AUTHORIZATION : uint8
{
	NOTHING_ALLOWED = 0,
	INCREMENT_MANDATORY,
	DECREMENT_MANDATORY,
	ALL_ALLOWED

};

UENUM()
enum class E_INTERRACTION_TYPE : uint8
{
	COLLISION = 0,
	TRANSFERT_TO_NEXT_ELEM,
	NOTHING_HAPPEN,
	DESTROY,
	AIR_TRANSFORMATION,
	FIRE_GENERATION,
	ICE_GENERATION,
	THUNDER_GENERATION

};

USTRUCT(BlueprintType)
struct FBlobElement
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	E_ELEMENT Element;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	E_PLAYABLE Playability;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	E_MAPPED_AUTHORIZATION  Authorization;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Value;
};




UCLASS()
class MYPROJECTTEST_API UBlobComponent : public UActorComponent
{
	GENERATED_BODY()

	
	// Sets default values for this component's properties

	UBlobComponent();

	UPROPERTY(EditAnywhere, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TArray<UBlobComponent*> OverlappingBlobs;



protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	/** Setup properties that should be replicated from the server to clients. */
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:	
		/** Please add a variable description */

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TArray<FBlobElement> Composition;
	//TMap<E_ELEMENT, int> composition;

	E_INTERRACTION_TYPE InteractionMatrix[static_cast<int32>(4)][static_cast<int32>(4)];

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	/** Please add a function description */
	UFUNCTION(BlueprintCallable)
	void interractElement();
	UFUNCTION(BlueprintCallable)
	int getElemValue(E_ELEMENT element);
	UFUNCTION(BlueprintCallable)
	int setElemValue(E_ELEMENT element, int value);
	UFUNCTION(BlueprintCallable)
	int incrementElemValue(int value, E_ELEMENT element);
	UFUNCTION(BlueprintCallable)
	int decrementElemValue(int value, E_ELEMENT element);
	UFUNCTION(BlueprintCallable)
	int chooseAction(E_ELEMENT	TargetElement, E_PLAYABLE	playability);
	UFUNCTION(BlueprintCallable)
	void setElementConfig(E_ELEMENT element, E_PLAYABLE	playability, E_MAPPED_AUTHORIZATION  Authorization, int Value);

	UFUNCTION(BlueprintCallable)
	void manageOnHitInteraction(UBlobComponent* TargetBlobComponent);

	UFUNCTION(BlueprintCallable)
	void addBlobInterraction(AActor* Actor);

	UFUNCTION(BlueprintCallable)
	void removeBlobInterraction(AActor* Actor);

	UFUNCTION()
	E_INTERRACTION_TYPE determineInteraction(E_ELEMENT elementBlob1, E_ELEMENT elementBlob2);

			
};
