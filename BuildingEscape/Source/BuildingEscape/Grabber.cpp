// Copyright Efren Cortes

#include "Grabber.h"
#include "Gameframework/Actor.h"
#define OUT
// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("Grabber reporting for duty"));
	// ...															   
	
	
}
// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// get the player viewpoint
	// ray casting (out to reach distance, like a laser to point at objects)
	//check for object in player vie
	APlayerController* playerCont = GetWorld()->GetFirstPlayerController();
	FVector PlayerViewPointLoc;
	FRotator PlayerViewPointRot;
	playerCont->GetPlayerViewPoint(
		OUT PlayerViewPointLoc,		//weird function, rather than return something
		OUT PlayerViewPointRot);	// it changes the variables passed to it, to the answer


	UE_LOG(LogTemp, Warning, TEXT("Location: %s, Rotation: %s"), 
		*PlayerViewPointLoc.ToString(), *PlayerViewPointRot.ToString()
		);
}

