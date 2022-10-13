// a

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "Components/CapsuleComponent.h"
#include "CapsuleTest.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNREALIS_API UCapsuleTest : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCapsuleTest();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UCapsuleComponent* Capsule;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
