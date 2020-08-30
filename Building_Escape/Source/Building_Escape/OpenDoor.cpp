// Placeholder


#include "OpenDoor.h"
#include "GameFramework\Actor.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	InitalYaw = GetOwner()->GetActorRotation().Yaw;
	CurrentYaw = InitalYaw;
	TargetRotation += InitalYaw;

	if (!PressurePlate)
	{
		UE_LOG(LogTemp, Error, TEXT("No pressure plate set, %s"), *GetOwner()->GetName());
	}

	ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (PressurePlate)
	{
		if (PressurePlate->IsOverlappingActor(ActorThatOpens))
		{
			OpenDoor(DeltaTime);
			DoorLastOpened = GetWorld()->GetTimeSeconds();
		}
		else if (!(PressurePlate->IsOverlappingActor(ActorThatOpens)))
		{
			if ((GetWorld()->GetTimeSeconds()) >= (DoorLastOpened + DoorOpenedDelay))
			{
				CloseDoor(DeltaTime);
			}
		}
	}
}

void UOpenDoor::OpenDoor(float DeltaTime)
{
	CurrentYaw = FMath::Lerp(CurrentYaw, TargetRotation, DoorOpenSpeed * DeltaTime);
	FRotator DoorRotation = GetOwner()->GetActorRotation();
	DoorRotation.Yaw = CurrentYaw;
	GetOwner()->SetActorRotation(DoorRotation);
}

void UOpenDoor::CloseDoor(float DeltaTime)
{
	CurrentYaw = FMath::Lerp(CurrentYaw, InitalYaw, DoorCloseSpeed * DeltaTime);
	FRotator DoorRotation = GetOwner()->GetActorRotation();
	DoorRotation.Yaw = CurrentYaw;
	GetOwner()->SetActorRotation(DoorRotation);
}