// Fill out your copyright notice in the Description page of Project Settings.


#include "blobActor.h"


// Sets default values
AblobActor::AblobActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BlobComponent = CreateDefaultSubobject<UBlobComponent>(TEXT("BlobComponent"));
	BlobComponent->SetIsReplicated(true);
	BlobComponent->setElementConfig(E_ELEMENT::EARTH, E_PLAYABLE::NORMAL, E_MAPPED_AUTHORIZATION::ALL_ALLOWED, 0);
	BlobComponent->setElementConfig(E_ELEMENT::WATER, E_PLAYABLE::NORMAL, E_MAPPED_AUTHORIZATION::ALL_ALLOWED, 0);
	BlobComponent->setElementConfig(E_ELEMENT::FIRE, E_PLAYABLE::NORMAL, E_MAPPED_AUTHORIZATION::ALL_ALLOWED, 0);
	BlobComponent->setElementConfig(E_ELEMENT::AIR, E_PLAYABLE::NORMAL, E_MAPPED_AUTHORIZATION::ALL_ALLOWED, 0);

}

// Called when the game starts or when spawned
void AblobActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AblobActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

