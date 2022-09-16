// a

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Fireball.generated.h"

UCLASS()
class UNREALIS_API AFireball : public AActor
{
	GENERATED_BODY()

		DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FHasBeenDestroyed, AActor*, Self);

public:	
	// Sets default values for this actor's properties
	AFireball();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UStaticMeshComponent* Hitbox;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UStaticMeshComponent* GFX;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		float TranscurredTranslations = 0.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		float DesiredTranslations = 100;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		float MovementSpeed = 100.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		float Damage = 20.f;

	UPROPERTY()
		bool ShouldMove = false;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
		void SetMovementParameters(float SpeedToSetTo, float _DesiredTranslations);

	UFUNCTION(BlueprintCallable)
		void SetGFXAndHitbox(UStaticMesh* GFXMesh, UStaticMesh* HitboxMesh);

	UFUNCTION(BlueprintCallable)
		void MasterFunction(float SpeedToSetTo, float _DesiredTranslations, float DamageToSetTo, UStaticMesh* GFXMesh, UStaticMesh* HitboxMesh);

	UFUNCTION(BlueprintCallable)
		void SetDamage(float DamageToSetTo);

	UFUNCTION(BlueprintCallable)
		void StartMoving();

	FHasBeenDestroyed OnDestruction;

private:
	UFUNCTION()
		void Move();

};
