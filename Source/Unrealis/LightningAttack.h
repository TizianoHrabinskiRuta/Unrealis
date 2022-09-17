// a

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LightningAttack.generated.h"

UCLASS()
class UNREALIS_API ALightningAttack : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALightningAttack();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
