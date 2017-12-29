// Fill out your copyright notice in the Description page of Project Settings.

#include "KeysCounter.h"


// Sets default values
UKeysCounter::UKeysCounter()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void UKeysCounter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void UKeysCounter::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	CheckIfUnlocked();

	//if all the keys have been placed, then open the doors
	if (_allDoorsUnlocked)
		openAllDoors();

	else
		closeAllDoors();
}

void UKeysCounter::openAllDoors()
{
	for (AActor* door : _doorsInMap)
	{
		UMoveDoor* mDoor = door->FindComponentByClass<UMoveDoor>();

		if (mDoor)
			mDoor->Open();
	}
}

void UKeysCounter::closeAllDoors()
{
	for (AActor* door : _doorsInMap)
	{
		UMoveDoor* mDoor = door->FindComponentByClass<UMoveDoor>();

		if (mDoor)
			mDoor->Close();	
	}
}

//counts the number of keys correctly placed 
//sets allDoorsUnlocked to true if number of keys matches the size of the Tarray
void UKeysCounter::CheckIfUnlocked()
{
	_allDoorsUnlocked = true;

	for (AActor* door : _doorsInMap)
	{
		UMoveDoor* mDoor = door->FindComponentByClass<UMoveDoor>();

		if (mDoor && !mDoor->unlocked)
			_allDoorsUnlocked = false;				
	}
}

