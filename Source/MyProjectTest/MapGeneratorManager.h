// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "blobActor.h"
#include "BlobComponent.h"
#include "MapGeneratorManager.generated.h"

UENUM(BlueprintType)
enum class E_BlobType : uint8
{
	TREE UMETA(DisplayName = "Tree"),
	ROCK UMETA(DisplayName = "Human"),
	GROUND UMETA(DisplayName = "Ground"),
	MUD UMETA(DisplayName = "Mud"),
	ANIMAL UMETA(DisplayName = "Animal"),
	HUMAN UMETA(DisplayName = "Human"),
	ELEMENTAL_FIRE UMETA(DisplayName = "ElementalFire"),
	ELEMENTAL_WATER UMETA(DisplayName = "ElementalWater"),
	ELEMENTAL_EARTH UMETA(DisplayName = "ElementalEarth"),
	ELEMENTAL_AIR UMETA(DisplayName = "ElementalAir"),

};
/**
 * 
 */
UCLASS()
class MYPROJECTTEST_API UMapGeneratorManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable, Category = SomeCategory)
	AblobActor* GenerateBlobInWorld(E_BlobType BlobType, FVector Location);
	
	UFUNCTION(BlueprintCallable, Category = SomeCategory)
	void GenerateMap();
	
	
	
};
