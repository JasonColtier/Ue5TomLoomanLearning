// Fill out your copyright notice in the Description page of Project Settings.


#include "SInteractionComp.h"



// Sets default values for this component's properties
USInteractionComp::USInteractionComp()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USInteractionComp::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void USInteractionComp::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void USInteractionComp::PrimaryInteract()
{
	AActor* Owner = GetOwner();
	FVector Start;
	FRotator EyeRotation;
	Owner->GetActorEyesViewPoint(Start,EyeRotation);
	
	FVector End;
	FHitResult HitResult;
	FCollisionObjectQueryParams CollisionQueryParams;
	CollisionQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);
	GetWorld()->LineTraceSingleByObjectType(HitResult,Start,End,CollisionQueryParams);	
}
