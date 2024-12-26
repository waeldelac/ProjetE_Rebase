// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BlobComponent.h"
#include "UObject/Interface.h"
#include "BlobInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(NotBlueprintable)
class UBlobInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class MYPROJECTTEST_API IBlobInterface
{
	GENERATED_BODY()

		
		

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintCallable, Category = SomeCategory)
	virtual UBlobComponent* getBlobComponent() =0;

	UFUNCTION(BlueprintCallable, Category = "Component")
	virtual AActor* getActorOfBlob() = 0;
};
