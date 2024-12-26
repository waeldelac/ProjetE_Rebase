// Fill out your copyright notice in the Description page of Project Settings.


#include "BlobCaracter.h"


// Sets default values
ABlobCaracter::ABlobCaracter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MouseClickState = E_MOUSECLICK::IDLE;
	BlobArcaneTarget = TScriptInterface<IBlobInterface>();
	bLockTarget = false;
	BlobComponent = CreateDefaultSubobject<UBlobComponent>(TEXT("BlobComponent"));
	BlobComponent->SetIsReplicated(true);
	BlobComponent->setElementConfig(E_ELEMENT::EARTH, E_PLAYABLE::NORMAL, E_MAPPED_AUTHORIZATION::ALL_ALLOWED, 100);
	BlobComponent->setElementConfig(E_ELEMENT::WATER, E_PLAYABLE::NORMAL, E_MAPPED_AUTHORIZATION::ALL_ALLOWED, 100);
	BlobComponent->setElementConfig(E_ELEMENT::FIRE, E_PLAYABLE::NORMAL, E_MAPPED_AUTHORIZATION::ALL_ALLOWED, 100);
	BlobComponent->setElementConfig(E_ELEMENT::AIR, E_PLAYABLE::NORMAL, E_MAPPED_AUTHORIZATION::ALL_ALLOWED, 100);

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
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("mouse click: %d"),(int)MouseClickState));
	if ( MouseClickState != E_MOUSECLICK::IDLE  && bLockTarget == false  )
	{
		FHitResult result;

		APlayerController* PlayerController = Cast<APlayerController>(Controller);
		PlayerController->GetHitResultUnderCursor(ECC_Pawn, false, result);
		//if (result.GetActor()->GetClass()->ImplementsInterface(UBlobInterface::StaticClass()))
		//{
		TScriptInterface<IBlobInterface> NewBlobSelected;

		if (result.GetActor() != NULL && result.GetActor()->GetClass()->ImplementsInterface(UBlobInterface::StaticClass()))
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Hello2")));
			NewBlobSelected.SetObject(result.GetActor());
			NewBlobSelected.SetInterface(Cast<IBlobInterface>(result.GetActor()));
		}
		else
		{
			NewBlobSelected.SetObject(NULL);
			NewBlobSelected.SetInterface(NULL);
		}

		//AActor* NewBlobSelected = Cast<AActor>(result.GetActor());
		
		

		if (BlobArcaneTarget != NewBlobSelected)
		{
			BlobArcaneTarget.SetObject(NewBlobSelected.GetObject());
			BlobArcaneTarget.SetInterface(NewBlobSelected.GetInterface());
			//UpdateServerPlayerInput(SpellSelection, MouseClickState, BlobTarget, ElementSelection);
		}


	}

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

