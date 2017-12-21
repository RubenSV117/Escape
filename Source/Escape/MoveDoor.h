// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Engine/TriggerVolume.h"
#include "MoveDoor.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPE_API UMoveDoor : public UActorComponent
{
	GENERATED_BODY()
public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	UMoveDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	void OpenDoor();
	void CloseDoor();
	//return total mass inside the trigger in Kg
	float GetTotalMassInTrigger();

private:
	AActor* owner;

	UPROPERTY(VisibleAnywhere)
		float _openAngle = 180.0f;

	UPROPERTY(EditAnywhere)
		ATriggerVolume* _pressurePlate;

	//minimum mass to trigger the door opening
	UPROPERTY(EditAnywhere)
		float massThreshold = 30;

	UPROPERTY(VisibleAnywhere)
		float _timeLastEntered;

	float _openTime = .3f;
};
