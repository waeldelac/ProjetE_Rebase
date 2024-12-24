// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Net/UnrealNetwork.h"
#include "Element.h"
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
	GAIN

};

USTRUCT()
struct FBlobElement
{
	GENERATED_BODY()

	UPROPERTY()
	E_ELEMENT Element;

	UPROPERTY()
	E_PLAYABLE Playability;

	UPROPERTY()
	E_MAPPED_AUTHORIZATION  Authorization;

	UPROPERTY()
	int32 Value;
};

UCLASS()
class UElementTargetInteraction : public UObject
{
	GENERATED_BODY()

public:
	TMap<E_ELEMENT, E_INTERRACTION_TYPE> ElementInterraction;
};



UCLASS()
class MYPROJECTTEST_API UBlobComponent : public UActorComponent
{
	GENERATED_BODY()

	
	// Sets default values for this component's properties

	UBlobComponent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TArray<UBlobComponent*> BlobListInInterraction;



protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	/** Setup properties that should be replicated from the server to clients. */
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:	
		/** Please add a variable description */

	
	UPROPERTY(Replicated)
	TArray<FBlobElement> Composition;
	//TMap<E_ELEMENT, int> composition;
	UPROPERTY()
	TMap<E_ELEMENT, UElementTargetInteraction*> InterractionMapping;

	UElementTargetInteraction* EarthInterraction;
	UElementTargetInteraction* WaterInterraction;
	UElementTargetInteraction* FireInterraction;
	UElementTargetInteraction* AirInterraction;

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

	UFUNCTION()
	E_INTERRACTION_TYPE determineInteraction(E_ELEMENT elementBlob1, E_ELEMENT elementBlob2);

			
};
