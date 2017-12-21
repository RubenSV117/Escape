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
}

// Called every frame
void UMoveDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (GetTotalMassInTrigger() >= massThreshold)
	{
		OpenDoor();
		_timeLastEntered = GetWorld()->GetTimeSeconds();
	}

	if (_timeLastEntered != 0 && GetWorld()->GetTimeSeconds() - _timeLastEntered > _openTime)
		CloseDoor();	
}

void UMoveDoor::OpenDoor()
{	
	owner->SetActorRotation(FRotator(0.f, _openAngle, 0.f));
}

void UMoveDoor::CloseDoor()
{
	owner->SetActorRotation(FRotator(0.f, 90.f, 0.f));
}

float UMoveDoor::GetTotalMassInTrigger()
{
	float totalMass = 0;

	TArray<AActor*> objectsInTrigger;

	_pressurePlate->GetOverlappingActors(OUT objectsInTrigger);

	for (AActor* actor : objectsInTrigger)
	{
		totalMass += actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
	}
	
	return totalMass;
}

