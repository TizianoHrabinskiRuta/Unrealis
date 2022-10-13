// a

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/SphereComponent.h"
#include "PickupBehaviorComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNREALIS_API UPickupBehaviorComponent : public UActorComponent
{
	GENERATED_BODY()

		DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPlayerDetectionDelegate, AActor*, PlayerRef);

public:	
	// Sets default values for this component's properties
	UPickupBehaviorComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
			bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class USphereComponent* SpherePickupRadius;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(BlueprintAssignable)
		FPlayerDetectionDelegate OnPlayerPickup;
		
};
