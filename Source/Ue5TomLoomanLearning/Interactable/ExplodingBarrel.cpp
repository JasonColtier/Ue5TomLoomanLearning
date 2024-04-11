// Fill out your copyright notice in the Description page of Project Settings.


#include "ExplodingBarrel.h"

#include <LogTools/LogTools.h>

#include "Logging/StructuredLog.h"
#include "PhysicsEngine/RadialForceComponent.h"


// Sets default values
AExplodingBarrel::AExplodingBarrel()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("Static Mesh");
	RadialForceComponent = CreateDefaultSubobject<URadialForceComponent>("Radial Force");

	StaticMesh->SetupAttachment(RootComponent);
	OnActorBeginOverlap.AddDynamic(this,&AExplodingBarrel::OnBeginOverlapp);

}

// Called when the game starts or when spawned
void AExplodingBarrel::BeginPlay()
{
	Super::BeginPlay();
	
}

void AExplodingBarrel::OnBeginOverlapp(AActor* SelfActor, AActor* OtherActor)
{
	Explode();
}

void AExplodingBarrel::Explode()
{
	RadialForceComponent->FireImpulse();
	SetLifeSpan(0.1);
}

void AExplodingBarrel::PostInitializeComponents()
{
	Super::PostInitializeComponents();

}

// Called every frame
void AExplodingBarrel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

