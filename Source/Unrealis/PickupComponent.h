// a

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/CapsuleComponent.h"
#include "PickupComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNREALIS_API UPickupComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPickupComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		class UCapsuleComponent* CapsulePickupRadius;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(Blueprintcallable)
		void AttachToParent(USceneComponent* Parent);
};
