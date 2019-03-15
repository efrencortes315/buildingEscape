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
	
	// ...
	
}

void UOpenDoor::OpenDoor()
{
	FString ownerName = GetOwner()->GetName();
	AActor* owner = GetOwner();
	FRotator oldRotation = owner->GetActorRotation();
	auto newZed = oldRotation.Yaw + 70;
	owner->SetActorRotation(FRotator(oldRotation.Pitch, newZed, oldRotation.Roll));
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// poll the trigger volume (check for condition each step)
	// if the ActorThatOpens is in the volume, then we open the door
	if (PressurePlate->IsOverlappingActor(ActorThatOoens)) {
		OpenDoor();
	}
}

