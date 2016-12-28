// hi please Dont Copy Ok

#pragma once

#include "Components/ActorComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ROOMESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;


private:
	 //How far we need to Draw Line
	float Reach;


	UPhysicsHandleComponent* PhysicsHandle = nullptr;

	UInputComponent *PawnInputComponent = nullptr;

	//Function for grabbing things that appears in our ray
	void Grab();

	//Function for releasing grabbed things that appears in our ray
	void GrabReleased();

	//Finds if there is a phsyics Handle
	void FindPhysicsHandle();

	//setup input binding if input component found
	void SetUpInputComponent();

	//Returns Hit for first physics body in reach
	const FHitResult GetFirstPhysicsBodyInReach();
	
};
