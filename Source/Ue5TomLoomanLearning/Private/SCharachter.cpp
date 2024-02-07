// Fill out your copyright notice in the Description page of Project Settings.


#include "SCharachter.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "LogTools/LogTools.h"

// Sets default values
ASCharachter::ASCharachter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");

	SpringArmComponent->SetupAttachment(RootComponent);
	CameraComponent->SetupAttachment(SpringArmComponent);
}

// Called when the game starts or when spawned
void ASCharachter::BeginPlay()
{
	Super::BeginPlay();
	
	
}

// Called every frame
void ASCharachter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ASCharachter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (auto PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(InputMappingContext, 0);
		}
	}
	
	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	EnhancedInputComponent->BindAction(IA_MoveX,ETriggerEvent::Triggered,this,&ASCharachter::EnhancedInputMoveX);
	EnhancedInputComponent->BindAction(IA_MoveY,ETriggerEvent::Triggered,this,&ASCharachter::EnhancedInputMoveY);
}

void ASCharachter::EnhancedInputMoveX(const FInputActionValue& Value)
{
	TRACE("MOVE ! %s",*Value.ToString())
	AddMovementInput(FVector::RightVector,Value.Get<float>());
}

void ASCharachter::EnhancedInputMoveY(const FInputActionValue& Value)
{
	TRACE("MOVE ! %s",*Value.ToString())
	AddMovementInput(FVector::ForwardVector,Value.Get<float>());
}

