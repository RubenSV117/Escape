// Fill out your copyright notice in the Description page of Project Settings.

#include "MoveDoor.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"

#define OUT

// Sets default values for this component's properties
UMoveDoor::UMoveDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UMoveDoor::BeginPlay()
{
	Super::BeginPlay();
	
	owner = GetOwner();

	if (!_pressurePlate)
		UE_LOG(LogTemp, Error, TEXT("%s does not have a trigger volume assigned"), *owner->GetName());
}

// Called every frame
void UMoveDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (InspectObjectsInTrigger() >= massThreshold && hasCorrectColor)
		_onOpen.Broadcast();
	
	else
	{
		_onClose.Broadcast();
		hasCorrectColor = false;
	}
}

float UMoveDoor::InspectObjectsInTrigger()
{
	float totalMass = 0;

	TArray<AActor*> objectsInTrigger;

	if(_pressurePlate)
		_pressurePlate->GetOverlappingActors(OUT objectsInTrigger);

	for (AActor* actor : objectsInTrigger)
	{
		totalMass += actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();

		if(actor->ActorHasTag(color)) 
			hasCorrectColor = true;

	}
	
	return totalMass;
}

