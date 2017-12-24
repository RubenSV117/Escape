// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MoveDoor.h"
#include "KeyCounter.generated.h"

UCLASS()
class ESCAPE_API UKeyCounter : public UActorComponent
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	UKeyCounter();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void openAllDoors();

	//counts the number of keys correctly placed 
	void countKeys();

private: 
	UPROPERTY(EditAnywhere)
		TArray<UMoveDoor*> _doorsInMap;

	UPROPERTY(EditAnywhere)
		int _unlockedDoors = 0;

	UPROPERTY(VisibleAnywhere)
		bool _allDoorsUnlocked = false;
	
	
};
