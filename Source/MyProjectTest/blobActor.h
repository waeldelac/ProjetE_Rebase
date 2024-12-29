// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BlobComponent.h"
#include "BlobInterface.h"
#include "blobActor.generated.h"

UENUM(BlueprintType)
enum class E_BlobType : uint8
{
	TREE UMETA(DisplayName = "Tree"),
	GROUND UMETA(DisplayName = "Ground"),
	MUD UMETA(DisplayName = "Mud"),
	ANIMAL UMETA(DisplayName = "Animal"),
	HUMAN UMETA(DisplayName = "Human"),

};

UCLASS()
class MYPROJECTTEST_API AblobActor : public AActor, public IBlobInterface
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UBlobComponent* BlobComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
	E_BlobType BlobType;

	
public:	
	// Sets default values for this actor's properties
	AblobActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	UFUNCTION(BlueprintCallable, Category = SomeCategory)
	UBlobComponent* getBlobComponent() { return BlobComponent; };
	UFUNCTION(BlueprintCallable, Category = SomeCategory)
	AActor* getActorOfBlob() override { return Cast<AActor>(this); };
	virtual void Tick(float DeltaTime) override;

	
	
};
