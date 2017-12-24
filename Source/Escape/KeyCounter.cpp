// Fill out your copyright notice in the Description page of Project Settings.

#include "KeyCounter.h"


// Sets default values
UKeyCounter::UKeyCounter()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void UKeyCounter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void UKeyCounter::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//if all the keys have been placed, then open the doors
	if (_allDoorsUnlocked)
		openAllDoors();
}

void UKeyCounter::openAllDoors()
{
	for (UMoveDoor* door : _doorsInMap)
	{
		door->onOpen.Broadcast();
	}
}

//counts the number of keys correctly placed 
//sets allDoorsUnlocked to true if number of keys matches the size of the Tarray
void UKeyCounter::countKeys()
{
	_allDoorsUnlocked = false;

	for (UMoveDoor* door : _doorsInMap)
	{
		if (door->InspectObjectsInTrigger() >= door->massThreshold && door->hasCorrectColor)
			_unlockedDoors++;

		else
		{
			door->onClose.Broadcast();
			door->hasCorrectColor = false;
		}
	}

	if (_unlockedDoors == _doorsInMap.Num())
		_allDoorsUnlocked = true;
}

