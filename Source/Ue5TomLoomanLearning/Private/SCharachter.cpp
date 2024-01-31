// Fill out your copyright notice in the Description page of Project Settings.


#include "Ue5TomLoomanLearning/Public/SCharachter.h"


// Sets default values
ASCharachter::ASCharachter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
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
}

