// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"



// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("Grabber reporting for duty!"));
	
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(_playerPosition, _playerRotation);

	//UE_LOG(LogTemp, Warning, TEXT("Position: %s  Rotation: %s"), *PlayerPosition.ToString(), *PlayerRotation.ToString());

	FVector LineEnd;
	//.vector() makes an FRotator into a unit vector
	LineEnd = _playerPosition + (_playerRotation.Vector() * _reach);

	DrawDebugLine(GetWorld(), _playerPosition, LineEnd, FColor(255, 0, 0), false, 0, 0, 1.f);

	// ...
}

