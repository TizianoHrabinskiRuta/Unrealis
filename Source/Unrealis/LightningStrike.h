// a

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LightningStrike.generated.h"

UCLASS()
class UNREALIS_API ALightningStrike : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALightningStrike();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
