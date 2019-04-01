// Copyright Efren Cortes

#include "OpenDoor.h"
#include "Gameframework/Actor.h"
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
	
	ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
	owner = GetOwner();
	// ...
	
}

void UOpenDoor::OpenDoor()
{
	FRotator oldRotation = owner->GetActorRotation();
	auto newZed = oldRotation.Yaw + 70;
	owner->SetActorRotation(FRotator(oldRotation.Pitch, newZed, oldRotation.Roll));
}
void UOpenDoor::CloseDoor()
{
	FRotator oldRotation = owner->GetActorRotation();
	auto newZed = oldRotation.Yaw - 70;
	owner->SetActorRotation(FRotator(oldRotation.Pitch, newZed, oldRotation.Roll));
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// poll the trigger volume (check for condition each step)
	// if the ActorThatOpens is in the volume, then we open the door
	if (PressurePlate->IsOverlappingActor(ActorThatOpens) && !isOpen) {
		OpenDoor();
		isOpen = true;
		lastDoorOpenTime = GetWorld()->GetTimeSeconds();
	}

	//check if its time to close the door
	if (isOpen && GetWorld()->GetTimeSeconds() - lastDoorOpenTime >= DoorCloseDelay) {
		if (!PressurePlate->IsOverlappingActor(ActorThatOpens)) {
			CloseDoor();
			isOpen = false;
		}
		else {
			lastDoorOpenTime = GetWorld()->GetTimeSeconds();
		}
		
	}
}

