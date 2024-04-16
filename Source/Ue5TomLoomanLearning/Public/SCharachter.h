// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SCharachter.generated.h"

class USInteractionComp;
struct FInputActionValue;
class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
class UAnimMontage;

UCLASS()
class UE5TOMLOOMANLEARNING_API ASCharachter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASCharachter();

protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USpringArmComponent> SpringArmComponent;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UCameraComponent> CameraComponent;

	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputMappingContext> InputMappingContext;

	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> IA_MoveX;

	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> IA_MoveY;

	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> IA_CamYaw;

	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> IA_CamPitch;

	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> IA_Jump;

	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> IA_PrimaryAction;

	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> IA_PrimaryInteract;

	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> IA_SecondaryAction;
	
	UPROPERTY(EditAnywhere)
	TObjectPtr<USInteractionComp> InteractionComp;

	UPROPERTY(EditAnywhere, Category="Attack")
	TObjectPtr<UAnimMontage> AttackAnim;
	
	UPROPERTY(EditAnywhere, Category="Attack")
	TSubclassOf<AActor> ProjectileClass;

	UPROPERTY(EditAnywhere, Category="Attack")
	TSubclassOf<AActor> SecondaryProjectileClass;


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
	void EnhancedInputJump(const FInputActionValue& Value);
	void PrimaryAttack(const FInputActionValue& Value);
	void SecondaryAttack(const FInputActionValue& Value);
	void PrimaryInteract(const FInputActionValue& Value);

	void SpawnProjectile(TSubclassOf<AActor> ProjectileClass);
};
