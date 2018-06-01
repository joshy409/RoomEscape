// Copyright Joshua Yang 2018


#include "OpenDoor.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include <string>
#define OUT


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
	Owner = GetOwner();
}

void UOpenDoor::OpenDoor()
{
	Owner->SetActorRotation(FRotator(0.0f, OpenAngle, 0.0f));
}

void UOpenDoor::CloseDoor()
{
	Owner->SetActorRotation(FRotator(0.0f, 180.0f, 0.0f));
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// poll the trigger volume
	// if the ActorThatOPens is in the volume
	if (GetTotalMassofActorsOnPlate() > 30.f) {
		OpenDoor();
		LastDoorOpenTime = GetWorld()->GetTimeSeconds();
	}
	
	//check if it's time to close the door
	if (GetWorld()->GetTimeSeconds() - LastDoorOpenTime > DoorCloseDelay) {
		CloseDoor();
	}

}

float UOpenDoor::GetTotalMassofActorsOnPlate()
{
	float TotalMass = 0.f;
	// fid all overlapping actors

	// takes care of nullptr crash
	if (!PressurePlate) {
		return TotalMass;
	}
	TArray<AActor*> OverlappingActors;
	PressurePlate->GetOverlappingActors(OUT OverlappingActors);
	// iterate through them adding their masses
	
	for (const auto* Actor : OverlappingActors) {
		
		TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
		std::string b = std::to_string(TotalMass);
		FString a(b.c_str());
		UE_LOG(LogTemp, Warning, TEXT("Total Mass on plate is %s"), *(a));
		UE_LOG(LogTemp, Warning, TEXT("%s on pressure plate"), *Actor->GetName());
	}
	return TotalMass;
}

