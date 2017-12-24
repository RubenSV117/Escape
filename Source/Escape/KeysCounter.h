// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MoveDoor.h"
#include "KeysCounter.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPE_API UKeysCounter : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	UKeysCounter();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void openAllDoors();
	void closeAllDoors();
	//counts the number of keys correctly placed 
	void CheckIfUnlocked();

private:
	UPROPERTY(EditAnywhere)
		TArray<AActor*> _doorsInMap;

	UPROPERTY(VisibleAnywhere)
		bool _allDoorsUnlocked = false;
};
