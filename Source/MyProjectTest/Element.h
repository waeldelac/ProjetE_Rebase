// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"


UENUM(BlueprintType)
enum class E_ELEMENT : uint8
{
    EARTH UMETA(DisplayName = "EARTH"),
    WATER UMETA(DisplayName = "WATER"),
    FIRE UMETA(DisplayName = "FIRE"),
    AIR UMETA(DisplayName = "AIR"),
    ETHER UMETA(DisplayName = "ETHER")
};



#include "Element.generated.h"



