// Placeholder

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include <Runtime\Engine\Classes\Engine\TriggerVolume.h>

#include "OpenDoor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDING_ESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void OpenDoor(float DeltaTime);
	void CloseDoor(float DeltaTime);

private:
	float InitalYaw;
	float CurrentYaw;
	float DoorLastOpened = 0.f;

	UPROPERTY(EditAnywhere)
	float DoorOpenedDelay = 2.f;

	UPROPERTY(EditAnywhere)
	float TargetRotation = 90.f;

	UPROPERTY(EditAnywhere)
	ATriggerVolume* PressurePlate;

	UPROPERTY(EditAnywhere)
	AActor* ActorThatOpens;

	UPROPERTY(EditAnywhere)
	float DoorOpenSpeed = 0.8f;

	UPROPERTY(EditAnywhere)
	float DoorCloseSpeed = 2.f;
};
