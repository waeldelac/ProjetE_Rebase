// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Net/UnrealNetwork.h"
#include "Element.h"
#include "BlobInterface.h"
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

/*
USTRUCT()
struct FPendingInteraction
{
	GENERATED_BODY()

	UPROPERTY()
	TArray<FPendingInteractionItem> PendingInteraction;
};

USTRUCT()
struct FPendingInteractionItem
{
	GENERATED_BODY()

	// Liste des interactions à effectuer
	UPROPERTY()
	E_INTERRACTION_TYPE PendingInteraction;
	UPROPERTY()
	E_ELEMENT Element;
	UPROPERTY()
	int32 TimeStamp;


	FPendingInteractionItem(E_INTERRACTION_TYPE InPendingInteraction, E_ELEMENT InElement, int32 InTimeStamp)
		: PendingInteraction(InPendingInteraction)
		, Element(InElement)
		, TimeStamp(InTimeStamp)
	{
	}

};*/




UCLASS()
class MYPROJECTTEST_API UBlobComponent : public UActorComponent
{
	GENERATED_BODY()

	
	// Sets default values for this component's properties

	UBlobComponent();

	/*UPROPERTY(EditAnywhere, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TMap<UBlobComponent*, E_INTERACTION_STATE> OverlappingBlobs;

	UPROPERTY(EditAnywhere, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TMap<UBlobComponent*, FPendingInteraction> PendingInteractions;*/






protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	/** Setup properties that should be replicated from the server to clients. */
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:	
		/** Please add a variable description */

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TArray<FBlobElement> Composition;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	UFUNCTION(BlueprintCallable, Category = "Blob Initialization")
	void InitializeBlobComposition(int32 EarthValue, int32 WaterValue, int32 FireValue, int32 AirValue);
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
	E_ELEMENT getElementInInteraction();
};
