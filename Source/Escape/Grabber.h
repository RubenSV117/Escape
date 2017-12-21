// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Components/InputComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "Grabber.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	//Returns the first object hit within range that is a physics body
	FHitResult GetFirstObjectHit();
	
	//Binds the first object hit to the physics grabber
	void Grab();
	
	//Releases object grabbed
	void Release();
	
	//Binds the physics handle 
	void FindPhysicsHandle();
	
	//Binds player input
	void BindInput();
	
	//current start of the reach range
	FVector GetReachLineStart();
	
	//current end of the reach range
	FVector GetReachLineEnd();
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
		FVector _playerPosition;

	UPROPERTY(EditAnywhere)
		FRotator _playerRotation;

	UPROPERTY(EditAnywhere)
	float _reach = 150.f;

	UPhysicsHandleComponent* _physicsHandle = nullptr;

	UInputComponent* _inputComponent = nullptr;
};
