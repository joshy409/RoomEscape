// Copyright Joshua Yang 2018

#include "TextRender.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#define OUT

// Sets default values for this component's properties
UTextRender::UTextRender()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTextRender::BeginPlay()
{
	Super::BeginPlay();

	ActivatingActor = GetWorld()->GetFirstPlayerController()->GetPawn();
	
	Owner = GetOwner();
}


// Called every frame
void UTextRender::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// poll the trigger volume
	// if player is standing in pressure plate 1
	if (PressurePlate && PressurePlate->IsOverlappingActor(ActivatingActor)) {
		// show  text render
		OnTrigger.Broadcast();
	}
	else 
	{
		OffTrigger.Broadcast();
	}
}
