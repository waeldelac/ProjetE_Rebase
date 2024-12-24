// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BlobInterface.h"
#include "BlobComponent.h"
#include "BlobCaracter.generated.h"

UENUM(BlueprintType)
enum class E_ARCANE : uint8
{
	MANIPULATE UMETA(DisplayName = "^Mainipulate"),
	CONJURATE UMETA(DisplayName = "^Conjurate"),
	TRANSMUTATE UMETA(DisplayName = "^Transmutate"),
	TRANSFERT UMETA(DisplayName = "^Transfert"),

};

UENUM(BlueprintType)
enum class E_MOUSECLICK : uint8
{
	IDLE UMETA(DisplayName = "^Idle"),
	RIGHTCLICK UMETA(DisplayName = "RightCLick"),
	LEFTCLICK UMETA(DisplayName = "^LeftClick"),

};

UCLASS()
class MYPROJECTTEST_API ABlobCaracter : public ACharacter, public IBlobInterface
{
	GENERATED_BODY()


public:
	// Sets default values for this character's properties
	ABlobCaracter();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UBlobComponent* BlobComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
	E_ARCANE ArcaneSelected;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
	E_ELEMENT ElementSelection;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION(BlueprintCallable, Category = SomeCategory)
	UBlobComponent* getBlobComponent() { return BlobComponent; };
	UFUNCTION(BlueprintCallable, Category = SomeCategory)
	AActor* getActorOfBlob() override { return Cast<AActor>(this); };
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void OnLeftClickPressed();
	virtual void OnLeftClickReleased();
	virtual void OnRightClickPressed();
	virtual void OnRightClickReleased();


	
	
};
