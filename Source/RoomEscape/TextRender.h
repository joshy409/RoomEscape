// Copyright Joshua Yang 2018

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/TextRenderComponent.h"
#include "Engine/TriggerVolume.h"
#include "Runtime/Core/Public/Delegates/Delegate.h"
#include "TextRender.generated.h"
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTriggerTextRender);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ROOMESCAPE_API UTextRender : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTextRender();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY(EditAnywhere)
		ATriggerVolume* PressurePlate = nullptr;

	UPROPERTY(BlueprintAssignable)
		FTriggerTextRender OnTrigger;

	UPROPERTY(BlueprintAssignable)
		FTriggerTextRender OffTrigger;

	// gets the owner name
	AActor* Owner;

	// only player will be able trigger  text render
	AActor* ActivatingActor;
};
