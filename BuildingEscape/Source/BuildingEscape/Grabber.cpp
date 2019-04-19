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
	///look for attatched physics handle
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle) {

	}
	else {
		UE_LOG(LogTemp, Error, TEXT("Error: %s is missing a UPhysicsHandleComponent"), *(GetOwner()->GetName()))
	}
	
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


	/*UE_LOG(LogTemp, Warning, TEXT("Location: %s, Rotation: %s"), 
		*PlayerViewPointLoc.ToString(), *PlayerViewPointRot.ToString()
		);*/
	/*UE_LOG(LogTemp, Warning, TEXT("Rotation: %s"),
		*PlayerViewPointRot.Vector().ToString()
	);*/
	//draw a red trace in the world to visualize
	
	FVector LineTraceEnd = PlayerViewPointLoc + PlayerViewPointRot.Vector() * reach;

	DrawDebugLine(
		GetWorld(),PlayerViewPointLoc,LineTraceEnd,FColor(255,0,0),false,0,0,10.f
	);

	//set up query parameters
	FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());

	FHitResult Hit;
	GetWorld()->LineTraceSingleByObjectType(
		OUT Hit, PlayerViewPointLoc, LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParams
	);
	
	AActor* actorName = Hit.GetActor();
	if (actorName) {
		UE_LOG(LogTemp, Warning, TEXT("Object within reach : %s"), *(actorName->GetName()));
	}
		
	
}

