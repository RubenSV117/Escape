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
	_reach = 100.f;

	_physicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();

	//if its still null, the address will be 0 and equal to false
	if (_physicsHandle)
	{

	}

	else
		UE_LOG(LogTemp, Error, TEXT("%s does not have a UPhysicsHandleComponent attached"), *GetOwner()->GetName());
	
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(_playerPosition, _playerRotation);

	//UE_LOG(LogTemp, Warning, TEXT("Position: %s  Rotation: %s"), *PlayerPosition.ToString(), *PlayerRotation.ToString());

	//The end point of the debugLine
	FVector lineEnd;

	//.vector() makes an FRotator into a unit vector
	lineEnd = _playerPosition + (_playerRotation.Vector() * _reach);

	DrawDebugLine(GetWorld(), _playerPosition, lineEnd, FColor(255, 0, 0), false, 0, 0, 1.f);

	//stores info about object hit
	FHitResult hit;

	//first param currently doesn't do anything, false that it uses the complex rendering mesh as collider
	//GetOwner() to ignore the owner, the player, since the LineTrace originates from the player
	FCollisionQueryParams traceParameters(FName(TEXT("")), false, GetOwner());

	GetWorld()->LineTraceSingleByObjectType(
		hit,
		_playerPosition,
		lineEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		traceParameters);
	
	
	AActor* objectHit = hit.GetActor();

	//if it hit an appropriate object
	if(objectHit)
		UE_LOG(LogTemp, Warning, TEXT("Can grab object: %s"), *objectHit->GetName());

}

