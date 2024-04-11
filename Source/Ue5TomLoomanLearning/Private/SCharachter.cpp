// Fill out your copyright notice in the Description page of Project Settings.


#include "SCharachter.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "LogTools/LogTools.h"
#include "Ue5TomLoomanLearning/Interactable/SInteractionComp.h"

// Sets default values
ASCharachter::ASCharachter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArmComponent->bUsePawnControlRotation = true;


	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	InteractionComp = CreateDefaultSubobject<USInteractionComp>("InteractionComp");

	SpringArmComponent->SetupAttachment(RootComponent);
	CameraComponent->SetupAttachment(SpringArmComponent);

	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
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
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<
			UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(InputMappingContext, 0);
		}
	}

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	EnhancedInputComponent->BindAction(IA_MoveX, ETriggerEvent::Triggered, this, &ASCharachter::EnhancedInputMoveX);
	EnhancedInputComponent->BindAction(IA_MoveY, ETriggerEvent::Triggered, this, &ASCharachter::EnhancedInputMoveY);
	EnhancedInputComponent->BindAction(IA_CamYaw, ETriggerEvent::Triggered, this, &ASCharachter::EnhancedInputTurn);
	EnhancedInputComponent->BindAction(IA_CamPitch, ETriggerEvent::Triggered, this, &ASCharachter::EnhancedInputPitch);
	EnhancedInputComponent->BindAction(IA_PrimaryAction, ETriggerEvent::Started, this, &ASCharachter::PrimaryAttack);
	EnhancedInputComponent->BindAction(IA_PrimaryInteract, ETriggerEvent::Started, this,
	                                   &ASCharachter::PrimaryInteract);
}

void ASCharachter::EnhancedInputMoveX(const FInputActionValue& Value)
{
	// TRACE("MOVE X ! %s",*Value.ToString())
	AddMovementInput(GetActorRightVector(), Value.Get<float>());
}

void ASCharachter::EnhancedInputMoveY(const FInputActionValue& Value)
{
	// TRACE("MOVE Y ! %s",*Value.ToString())
	AddMovementInput(GetViewRotation().Vector(), Value.Get<float>());
}

void ASCharachter::EnhancedInputTurn(const FInputActionValue& Value)
{
	// TRACE("Turn ! %s",*Value.ToString())
	AddControllerYawInput(Value.Get<float>());
}

void ASCharachter::EnhancedInputPitch(const FInputActionValue& Value)
{
	// TRACE("Pitch ! %s",*Value.ToString())
	AddControllerPitchInput(Value.Get<float>());
}

void ASCharachter::PrimaryAttack(const FInputActionValue& Value)
{
	PlayAnimMontage(AttackAnim);
	FTimerHandle Handle;
	GetWorld()->GetTimerManager().SetTimer(Handle, [this]
	{
		TRACE("Spawn Projectile !");
		const FTransform SpawnTM = FTransform(GetActorRotation(), GetMesh()->GetSocketLocation("Muzzle_01"));
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnParams.Instigator = this;
		GetWorld()->SpawnActor<AActor>(ProjectileClass, SpawnTM, SpawnParams);
	}, 0.2, false);
}

void ASCharachter::PrimaryInteract(const FInputActionValue& Value)
{
	TRACE("PrimaryInteract");
	InteractionComp->PrimaryInteract();
}
