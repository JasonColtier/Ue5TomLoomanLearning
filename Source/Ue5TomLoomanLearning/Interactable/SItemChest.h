// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Ue5TomLoomanLearning/Interface/SGameplayInterface.h"
#include "SItemChest.generated.h"

UCLASS()
class UE5TOMLOOMANLEARNING_API ASItemChest : public AActor , public ISGameplayInterface
{
	GENERATED_BODY()


public:

	UPROPERTY(EditAnywhere)
	float TargetPitch = 110;
	
	void Interact_Implementation(APawn* InstigatorPawn) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> BaseMesh;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> LidMesh;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	ASItemChest();

};
