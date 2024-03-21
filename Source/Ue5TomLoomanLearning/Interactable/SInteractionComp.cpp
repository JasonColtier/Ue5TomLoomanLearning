// Fill out your copyright notice in the Description page of Project Settings.


#include "SInteractionComp.h"

#include "LogTools/LogTools.h"
#include "Ue5TomLoomanLearning/Interface/SGameplayInterface.h"


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
void USInteractionComp::TickComponent(float DeltaTime, ELevelTick TickType,
                                      FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void USInteractionComp::PrimaryInteract()
{
	AActor* Owner = GetOwner();
	FVector Start;
	FRotator EyeRotation;
	Owner->GetActorEyesViewPoint(Start, EyeRotation);

	FVector End = Start + (EyeRotation.Vector() * InteractionDistance);
	//FHitResult HitResult;
	FCollisionObjectQueryParams CollisionQueryParams;
	CollisionQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);
	//bool bBlockingHit = GetWorld()->LineTraceSingleByObjectType(HitResult, Start, End, CollisionQueryParams);
	//DrawDebugLine(GetWorld(), Start, End, (bBlockingHit ? FColor::Blue : FColor::Red), false, 3, 0, 3);

	TArray<FHitResult> HitResults;
	bool bBlockingHit = GetWorld()->SweepMultiByObjectType(HitResults,Start,End,FQuat::Identity,CollisionQueryParams,FCollisionShape::MakeSphere(30));
	DrawDebugLine(GetWorld(), Start, End, (bBlockingHit ? FColor::Blue : FColor::Red), false, 3, 0, 30);

	for (auto HitResult : HitResults)
	{
		AActor* HitActor = HitResult.GetActor();
		if (HitActor)
		{
			TRACE("actor hit ! %s", *HitActor->GetClass()->GetName());
			if (HitActor->GetClass()->ImplementsInterface(USGameplayInterface::StaticClass()))
			{
				APawn* OwnerPawn = Cast<APawn>(GetOwner());
				ISGameplayInterface::Execute_Interact(HitActor, OwnerPawn);
				break;
			}
			else
			{
				TRACE_WARN("actor doesnt implement interface");
			}
		}
	}
	
	
}
