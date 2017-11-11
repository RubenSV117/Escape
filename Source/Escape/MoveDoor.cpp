// Fill out your copyright notice in the Description page of Project Settings.

#include "MoveDoor.h"
#include "GameFramework/Actor.h"


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
	AActor* owner = GetOwner();
	FRotator* rotation = new FRotator(0.f, 130.f, 0.f);
	owner->SetActorRotation(*rotation);
	// ...
	
}


// Called every frame
void UMoveDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

