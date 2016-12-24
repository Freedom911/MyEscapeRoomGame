// hi please Dont Copy Ok

#include "RoomEscape.h"
#include "Grabber.h"

#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;
	Reach = 100.f;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	FString ObjectName = GetOwner()->GetActorLabel();
	// ...
	
}


// Called every frame
void UGrabber::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// Get Player ViewPoint
	FRotator PlayerRotation;
	FVector PlayerLocation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		      OUT PlayerLocation, 
		      OUT  PlayerRotation);
	/*FString sLocation = PlayerLocation.ToString();
	FString sRotation = PlayerRotation.Vector().ToString();
	UE_LOG(LogTemp, Warning, TEXT("Position :  %s , Rotation: %s"), *sLocation, *sRotation)
*/
	FVector LineTraceDirection = PlayerRotation.Vector() * Reach;
	FVector LineTraceEnd = PlayerLocation + LineTraceDirection;

	//Draw a trace to visualize
	DrawDebugLine(
		GetWorld(),
		PlayerLocation,
		LineTraceEnd,
		FColor(255, 0, 0),
		false,
		0.f,
		0.f,
		10.f
		);

}

