// Fill out your copyright notice in the Description page of Project Settings.

#include "RoomEscape.h"
#include "OpenDoor.h"


// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;
	OpenAngle = -90.f;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	   
	ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();

	Owner = GetOwner();
	
}

void UOpenDoor::OpenDoor()
{
	if(Owner)
	Owner->SetActorRotation(FRotator(0, OpenAngle, 0));


}

void UOpenDoor::CloseDoor()
{
	if(Owner)
	Owner->SetActorRotation(FRotator(0, 0, 0));
}


// Called every frame
void UOpenDoor::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	float CurrentTime = GetWorld()->GetTimeSeconds();

	//Poll the Trigger Volume
	//If the ActorThatOpen is in the Volume
	if (PressurePlate->IsOverlappingActor(ActorThatOpens))
	{
		OpenDoor();
		LastDoorOpenTime = CurrentTime;
	}

	//Continusouly check time if it is to close
	if (CurrentTime - LastDoorOpenTime > DoorCloseDelay)
	{
		CloseDoor();
	}

}

