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


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* GFX;

	UPROPERTY(VisibleAnywhere)
		float Length = 1000.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		float Damage = 40.f;

	UFUNCTION()
		void StartOpacityChanges();

	//Look into UMaterial (maybe pass as param on component?) and try to access its opacity so a loop can decrease it until it is invisible, then destroy

	FTimerHandle GFXOpacityHandle;

public:	

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void SetParams(UStaticMesh* GFXMesh, FRotator Rotation);// Configures the lightning GFX

	UFUNCTION()
		void CheckForColission(FVector SpawnLocation, FVector ForwardsVector, FRotator Rotation, AActor* OwnerRef); // Raycasts for colission

	UFUNCTION()
		void SetDamage(float FDamage);

};
