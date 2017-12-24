// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/PrimitiveComponent.h"
#include "GameFramework/Actor.h"
#include "Engine/TriggerVolume.h"
#include "MoveDoor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDoorEvent);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPE_API UMoveDoor : public UActorComponent
{
	GENERATED_BODY()
public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	UMoveDoor();
	// Called when the game starts
	virtual void BeginPlay() override;
	//return total mass inside the trigger in Kg
	float InspectObjectsInTrigger();

	void DetermineLockedState();

	void Open();

	void Close();

	//set to true when at least one of the objects in the trigger is the right color
	UPROPERTY(VisibleAnywhere)
		bool hasCorrectColor = false;

	//minimum mass to trigger the door opening
	UPROPERTY(EditAnywhere)
		float massThreshold = 30;

	//will be set to true if it has sufficient mass and the correctColor
	UPROPERTY(VisibleAnywhere)
		bool unlocked = false;

	//event to trigger door opening
	UPROPERTY(BlueprintAssignable)
		FDoorEvent onOpen;

	//event to trigger door closing
	UPROPERTY(BlueprintAssignable)
		FDoorEvent onClose;

private:
	AActor* owner = nullptr;

	UPROPERTY(EditAnywhere)
		ATriggerVolume* _pressurePlate = nullptr;

	//color item needed for the door to open
	UPROPERTY(EditAnywhere)
		FName _color;


};
