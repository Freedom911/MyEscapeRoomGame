// Fill out your copyright notice in the Description page of Project Settings.

#include "RoomEscape.h"
#include "PositionReport.h"


// Sets default values for this component's properties
UPositionReport::UPositionReport()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPositionReport::BeginPlay()
{
	Super::BeginPlay();
	FString ObjectName = GetOwner()->GetActorLabel();
	FString ObjectPosition= (GetOwner()->GetActorLocation().ToString());
	
	UE_LOG(LogTemp, Warning, TEXT("Bastardo  %s your are 1 2 %d gone "),*ObjectName,3);

	UE_LOG(LogTemp, Warning, TEXT("Molto Bene this is  %s  "), *ObjectPosition);

	// ...
	
}


// Called every frame
void UPositionReport::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
}

