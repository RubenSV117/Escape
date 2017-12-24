// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"
//used to identify which variable are being changed in a function
#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	FindPhysicsHandle();
	BindInput();
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	if (_physicsHandle && _physicsHandle->GrabbedComponent)
			_physicsHandle->SetTargetLocation(GetReachLineEnd());
}

//grabs an object within range if it has a physics body
void UGrabber::Grab()
{
	FHitResult hitResult = GetFirstObjectHit();
	AActor* actorHit = hitResult.GetActor();

	if (actorHit)
	{
		UPrimitiveComponent* componentToGrab = hitResult.GetComponent(); //gets the mesh in this case
		FVector grabLocation = componentToGrab->GetOwner()->GetActorLocation();
		

		if (_physicsHandle)
			_physicsHandle->GrabComponent(componentToGrab, NAME_None, grabLocation, true);
	}
}

//LineCasts and returns the first object hit with a physics body
FHitResult UGrabber::GetFirstObjectHit()
{
	//stores info about object hit
	FHitResult hitResult;

	//first param currently doesn't do anything, false that it uses the complex rendering mesh as collider
	//GetOwner() to ignore the owner, the player, since the LineTrace originates from the player
	FCollisionQueryParams traceParameters(FName(TEXT("")), false, GetOwner());

	GetWorld()->LineTraceSingleByObjectType(
		OUT hitResult,
		GetReachLineStart(),
		GetReachLineEnd(),
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody), //only get the objects that have Simulate Physics checked
		traceParameters);

	AActor* objectHit = hitResult.GetActor();

	return hitResult;
}

//releases grabbed object
void UGrabber::Release()
{
	if (_physicsHandle && _physicsHandle->GrabbedComponent)
		_physicsHandle->ReleaseComponent();
}

//look for attached physicsHandle component
void UGrabber::FindPhysicsHandle()
{
	_physicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();

	if (_physicsHandle == nullptr)
		UE_LOG(LogTemp, Error, TEXT("%s does not have a UPhysicsHandleComponent attached"), *GetOwner()->GetName());
}

//look for and set up inputComponent attached at runtime
void UGrabber::BindInput()
{
	_inputComponent = GetOwner()->FindComponentByClass<UInputComponent>();

	//Bind the input actions
	if (_inputComponent)
	{
		_inputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		_inputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}

	else
		UE_LOG(LogTemp, Error, TEXT("_inputComponent has not been set"));
}

FVector UGrabber::GetReachLineStart()
{
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT _playerPosition, OUT _playerRotation);

	return _playerPosition;
}

FVector UGrabber::GetReachLineEnd()
{
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT _playerPosition, OUT _playerRotation);

	//The end point of the debugLine, .vector() makes an FRotator into a unit vector
	return _playerPosition + (_playerRotation.Vector() * _reach);
}
