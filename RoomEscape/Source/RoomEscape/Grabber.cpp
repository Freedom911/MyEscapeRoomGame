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

}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	FindPhysicsHandle();
	SetUpInputComponent();
	
}
///Look for the attached Physics Component
void UGrabber::FindPhysicsHandle()
{

	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();

	if (PhysicsHandle)
	{
		//Physics Handle Found
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Physics Handle Component Not Found For COmponent %s"), *(GetOwner()->GetName()))
	}
}

///Look For Attached Input Component and set binding
void UGrabber::SetUpInputComponent()
{
	//Input Component will appear only in Input Component
	PawnInputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (PawnInputComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("Input Component Found For Component: %s YO"), *(GetOwner()->GetName()))
        //Binding Input 
		PawnInputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		PawnInputComponent->BindAction("Grab", IE_Released, this, &UGrabber::GrabReleased);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Input Component Not Found For COmponent %s"), *(GetOwner()->GetName()))
	}
}


void UGrabber::Grab()
{
	UE_LOG(LogTemp, Warning, TEXT("Grab Key Pressed"))

    ///Line Trace and Try and reach any actors with physics body  collision channel

    ///If we found the actor then attach a physics handle
	auto Hit = GetFirstPhysicsBodyInReach();
	auto ComponentToGrab = Hit.GetComponent();


	//If we hit an actor then only attach the component
	if (Hit.GetActor())
	{
		PhysicsHandle->GrabComponent(
			ComponentToGrab,
			NAME_None,
			ComponentToGrab->GetOwner()->GetActorLocation(),
			true
			);

	}
}

void UGrabber::GrabReleased()
{
	UE_LOG(LogTemp, Warning, TEXT("Grab Key Released"))
    
		if (PhysicsHandle->GrabbedComponent)
		{
			PhysicsHandle->ReleaseComponent();
		}

}



// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	// Get Player ViewPoint
	FRotator PlayerRotation;
	FVector PlayerLocation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerLocation,
		OUT  PlayerRotation);

	FVector LineTraceDirection = PlayerRotation.Vector() * Reach;
	FVector LineTraceEnd = PlayerLocation + LineTraceDirection;
	//If the physics handle is attached then move the 
	//object we are holding
	if (PhysicsHandle->GrabbedComponent)
	{
		PhysicsHandle->SetTargetLocation(LineTraceEnd);
	}
	
}

const FHitResult UGrabber::GetFirstPhysicsBodyInReach()
{
	// Get Player ViewPoint
	FRotator PlayerRotation;
	FVector PlayerLocation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerLocation,
		OUT  PlayerRotation);

	FVector LineTraceDirection = PlayerRotation.Vector() * Reach;
	FVector LineTraceEnd = PlayerLocation + LineTraceDirection;


	///Set Up Query Parameters
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());


	///Line Trace to object
	FHitResult Hit;
	GetWorld()->LineTraceSingleByObjectType(
		OUT Hit,
		PlayerLocation,
		LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParameters
		);

	//See What we hit
	AActor* ActorHit = Hit.GetActor();
	if (ActorHit)
		UE_LOG(LogTemp, Warning, TEXT("Si LINE Trace hit  : %s"), *(ActorHit->GetName()))


		return Hit;
}

