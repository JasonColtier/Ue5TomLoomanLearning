﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SCharachter.generated.h"

struct FInputActionValue;
class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;

UCLASS()
class UE5TOMLOOMANLEARNING_API ASCharachter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASCharachter();

protected:

	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> ProjectileClass;
	
	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComponent;

	UPROPERTY(EditAnywhere,Category="Input")
	UInputMappingContext* InputMappingContext;

	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* IA_MoveX;

	UPROPERTY(EditAnywhere,Category="Input")
	UInputAction* IA_MoveY;
	
	UPROPERTY(EditAnywhere,Category="Input")
	UInputAction* IA_CamYaw;

	UPROPERTY(EditAnywhere,Category="Input")
	UInputAction* IA_CamPitch;

	
	UPROPERTY(EditAnywhere,Category="Input")
	UInputAction* IA_PrimaryAction;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void EnhancedInputMoveX(const FInputActionValue& Value);
	void EnhancedInputMoveY(const FInputActionValue& Value);
	void EnhancedInputTurn(const FInputActionValue& Value);
	void EnhancedInputPitch(const FInputActionValue& Value);
	void PrimaryAttack(const FInputActionValue& Value);
};
