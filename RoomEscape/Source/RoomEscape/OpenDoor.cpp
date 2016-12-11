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

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	AActor *Owner = GetOwner();

	FString Rots = Owner->GetActorRotation().ToString();

	UE_LOG(LogTemp, Error, TEXT("This is it %s"), *Rots)

	float iYaw = Owner->GetActorRotation().Yaw;
	float iRoll = Owner->GetActorRotation().Roll;
	float iPitch = Owner->GetActorRotation().Pitch;
	FRotator rRot(iPitch,-100,iRoll);
	Owner->SetActorRotation(rRot);

	   
	// ...
	
}


// Called every frame
void UOpenDoor::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
}

