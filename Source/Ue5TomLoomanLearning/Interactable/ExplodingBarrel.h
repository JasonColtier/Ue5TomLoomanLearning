// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ExplodingBarrel.generated.h"

class URadialForceComponent;

UCLASS()
class UE5TOMLOOMANLEARNING_API AExplodingBarrel : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AExplodingBarrel();

	UPROPERTY(EditAnywhere)
	TObjectPtr<UStaticMeshComponent> StaticMesh;

	UPROPERTY(EditAnywhere)
	TObjectPtr<URadialForceComponent> RadialForceComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void OnBeginOverlapp(AActor* SelfActor,AActor* OtherActor);


	UFUNCTION(CallInEditor)
	void Explode();
	
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
