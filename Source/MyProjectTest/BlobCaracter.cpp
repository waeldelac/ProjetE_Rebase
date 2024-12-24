// Fill out your copyright notice in the Description page of Project Settings.


#include "BlobCaracter.h"


// Sets default values
ABlobCaracter::ABlobCaracter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABlobCaracter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABlobCaracter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABlobCaracter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	/*if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {

		//Moving
		EnhancedInputComponent->BindAction(ArcaneLeft, ETriggerEvent::Triggered, this, &ABlobCaracter::OnLeftClickPressed());

	}*/

}

void ABlobCaracter::OnLeftClickPressed()
{
	UE_LOG(LogTemp, Log, TEXT("Left click pressed."));
}

void ABlobCaracter::OnLeftClickReleased()
{
	UE_LOG(LogTemp, Log, TEXT("Left click released."));
}

void ABlobCaracter::OnRightClickPressed()
{
	UE_LOG(LogTemp, Log, TEXT("Right click pressed."));
}

void ABlobCaracter::OnRightClickReleased()
{
	UE_LOG(LogTemp, Log, TEXT("Right click released."));
}

