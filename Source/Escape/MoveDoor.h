// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
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

private:
	AActor* owner;

	UPROPERTY(VisibleAnywhere)
		float _openAngle = 180.0f;

	UPROPERTY(EditAnywhere)
		ATriggerVolume* _pressurePlate;

	UPROPERTY(VisibleAnywhere)
		float _timeLastEntered;

	float _openTime = .3f;;

	AActor* _actorThatOpens;

};