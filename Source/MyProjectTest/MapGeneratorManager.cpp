// Fill out your copyright notice in the Description page of Project Settings.


#include "MapGeneratorManager.h"

AblobActor* UMapGeneratorManager::GenerateBlobInWorld(E_BlobType BlobType, FVector Location)
{
    // Obtenir le UWorld
    UWorld* World = GetWorld();
    if (!World)
    {
        UE_LOG(LogTemp, Error, TEXT("GenerateBlobInWorld: World is nullptr!"));
        return nullptr;
    }

    UE_LOG(LogTemp, Log, TEXT("GenerateBlobInWorld: World is valid."));

    // Charger la classe Blueprint
    FString BPPath = TEXT("/Game/ThirdPerson/Blueprints/BP_BlobActor.BP_BlobActor_C"); // Ajout du suffixe "_C"
    UClass* BPClass = LoadObject<UClass>(nullptr, *BPPath);

    if (!BPClass)
    {
        UE_LOG(LogTemp, Error, TEXT("GenerateBlobInWorld: Failed to load Blueprint class from path: %s"), *BPPath);
        return nullptr;
    }

    UE_LOG(LogTemp, Log, TEXT("GenerateBlobInWorld: Blueprint class loaded successfully."));

    // Vérifier que la classe est dérivée de AblobActor
    if (!BPClass->IsChildOf(AblobActor::StaticClass()))
    {
        UE_LOG(LogTemp, Error, TEXT("GenerateBlobInWorld: Loaded class is not a subclass of AblobActor."));
        return nullptr;
    }

    UE_LOG(LogTemp, Log, TEXT("GenerateBlobInWorld: Blueprint class is a valid subclass of AblobActor."));

    // Faire spawn l'acteur
    FActorSpawnParameters SpawnParams;
    AblobActor* NewBlob = Cast<AblobActor>(World->SpawnActor<AblobActor>(BPClass, Location, FRotator::ZeroRotator, SpawnParams));

    if (!NewBlob)
    {
        UE_LOG(LogTemp, Error, TEXT("GenerateBlobInWorld: Failed to spawn actor of type AblobActor."));
        return nullptr;
    }

    UE_LOG(LogTemp, Log, TEXT("GenerateBlobInWorld: Blob spawned successfully at location: %s"), *Location.ToString());

    // Configurer le blob selon son type
    switch (BlobType)
    {
    case E_BlobType::TREE:
        UE_LOG(LogTemp, Log, TEXT("GenerateBlobInWorld: Configuring blob as TREE."));
        break;
    case E_BlobType::ROCK:
        UE_LOG(LogTemp, Log, TEXT("GenerateBlobInWorld: Configuring blob as ROCK."));
        break;
    case E_BlobType::GROUND:
        UE_LOG(LogTemp, Log, TEXT("GenerateBlobInWorld: Configuring blob as GROUND."));
        NewBlob->getBlobComponent()->setElementConfig(E_ELEMENT::EARTH, E_PLAYABLE::INFINITE, E_MAPPED_AUTHORIZATION::ALL_ALLOWED, 0x7FFFFFFF);
        NewBlob->getBlobComponent()->setElementConfig(E_ELEMENT::WATER, E_PLAYABLE::ABSORB, E_MAPPED_AUTHORIZATION::ALL_ALLOWED, 0);
        NewBlob->getBlobComponent()->setElementConfig(E_ELEMENT::FIRE, E_PLAYABLE::ABSORB, E_MAPPED_AUTHORIZATION::ALL_ALLOWED, 0);
        NewBlob->getBlobComponent()->setElementConfig(E_ELEMENT::AIR, E_PLAYABLE::ABSORB, E_MAPPED_AUTHORIZATION::ALL_ALLOWED, 0);
        break;
    case E_BlobType::ELEMENTAL_EARTH:
        UE_LOG(LogTemp, Log, TEXT("GenerateBlobInWorld: Configuring blob as ELEMENTAL_EARTH."));
        NewBlob->getBlobComponent()->setElementConfig(E_ELEMENT::EARTH, E_PLAYABLE::NORMAL, E_MAPPED_AUTHORIZATION::ALL_ALLOWED, 1);
        break;
    case E_BlobType::ELEMENTAL_WATER:
        UE_LOG(LogTemp, Log, TEXT("GenerateBlobInWorld: Configuring blob as ELEMENTAL_WATER."));
        NewBlob->getBlobComponent()->setElementConfig(E_ELEMENT::WATER, E_PLAYABLE::NORMAL, E_MAPPED_AUTHORIZATION::ALL_ALLOWED, 1);
        break;
    case E_BlobType::ELEMENTAL_FIRE:
        UE_LOG(LogTemp, Log, TEXT("GenerateBlobInWorld: Configuring blob as ELEMENTAL_FIRE."));
        NewBlob->getBlobComponent()->setElementConfig(E_ELEMENT::FIRE, E_PLAYABLE::NORMAL, E_MAPPED_AUTHORIZATION::ALL_ALLOWED, 1);
        break;
    case E_BlobType::ELEMENTAL_AIR:
        UE_LOG(LogTemp, Log, TEXT("GenerateBlobInWorld: Configuring blob as ELEMENTAL_AIR."));
        NewBlob->getBlobComponent()->setElementConfig(E_ELEMENT::AIR, E_PLAYABLE::NORMAL, E_MAPPED_AUTHORIZATION::ALL_ALLOWED, 1);
        break;
    default:
        UE_LOG(LogTemp, Warning, TEXT("GenerateBlobInWorld: Unknown BlobType."));
        break;
    }

    return NewBlob;
}


void UMapGeneratorManager::GenerateMap()
{

}
