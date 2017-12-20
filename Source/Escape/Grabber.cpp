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

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT _playerPosition, OUT _playerRotation);

	//The end point of the debugLine
	//.vector() makes an FRotator into a unit vector
	FVector lineEnd = _playerPosition + (_playerRotation.Vector() * _reach);

	if (_physicsHandle->GrabbedComponent)
	{
		_physicsHandle->SetTargetLocation(lineEnd);
	}
}

//grabs an object within range if it has a physics body
void UGrabber::Grab()
{
	UE_LOG(LogTemp, Warning, TEXT("Object Grabbed"));

	FHitResult hit = GetFirstObjectHit();
	AActor* actorHit = hit.GetActor();

	if (actorHit)
	{
		UPrimitiveComponent* componentToGrab = hit.GetComponent();
		FVector grabLocation = componentToGrab->GetOwner()->GetActorLocation();
		_physicsHandle->GrabComponent(componentToGrab, NAME_None, grabLocation, true);
	}
}

//LineCasts and returns the first object hit with a physics body
FHitResult UGrabber::GetFirstObjectHit()
{
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT _playerPosition, OUT _playerRotation);
	
	//The end point of the debugLine
	//.vector() makes an FRotator into a unit vector
	FVector lineEnd = _playerPosition + (_playerRotation.Vector() * _reach);

	//DrawDebugLine(GetWorld(), _playerPosition, lineEnd, FColor(255, 0, 0), false, 0, 0, 1.f);

	//stores info about object hit
	FHitResult hit;

	//first param currently doesn't do anything, false that it uses the complex rendering mesh as collider
	//GetOwner() to ignore the owner, the player, since the LineTrace originates from the player
	FCollisionQueryParams traceParameters(FName(TEXT("")), false, GetOwner());

	GetWorld()->LineTraceSingleByObjectType(
		OUT hit,
		_playerPosition,
		lineEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody), //only get the objects that have Simulate Physics checked
		traceParameters);


	AActor* objectHit = hit.GetActor();

	//if it hit an appropriate object
	if (objectHit)
		UE_LOG(LogTemp, Warning, TEXT("Can grab object: %s"), *objectHit->GetName());

	return hit;
}

//releases grabbed object
void UGrabber::Release()
{
	UE_LOG(LogTemp, Warning, TEXT("Object Released"));

	if(_physicsHandle->GrabbedComponent)
		_physicsHandle->ReleaseComponent();
}

//look for attached physicsHandle component
void UGrabber::FindPhysicsHandle()
{
	_physicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();

	//if its still null, the address will be 0 and equal to false
	if (_physicsHandle)
	{

	}

	else
		UE_LOG(LogTemp, Error, TEXT("%s does not have a UPhysicsHandleComponent attached"), *GetOwner()->GetName());
}

//look for and set up inputComponent attached at runtime
void UGrabber::BindInput()
{
	_inputComponent = GetOwner()->FindComponentByClass<UInputComponent>();

	if (_inputComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("_inputComponent in grabber has been set"));

		//Bind the input actions
		_inputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		_inputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}

	else
		UE_LOG(LogTemp, Warning, TEXT("_inputComponent has not been set"));
}
