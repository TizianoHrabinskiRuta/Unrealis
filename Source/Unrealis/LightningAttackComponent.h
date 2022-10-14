// a

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LightningAttack.h"
#include "LightningAttackComponent.generated.h"



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNREALIS_API ULightningAttackComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	ULightningAttackComponent();

	

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly)
		bool IsInCooldown = false;

	UPROPERTY(BlueprintReadOnly)
		float AttackDamage = 50;

	UPROPERTY(BlueprintReadOnly)
		float CooldownTime = 1.f;

	UFUNCTION()
		void CooldownCallback();

	FTimerHandle CooldownHandle;

private:


public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
		void FireLightning(UStaticMesh* GFXMesh, FVector SpawnLocation, FVector ForwardsVector, FRotator SpawnRotation, AActor* OwnerReference); // For owner reference, pass a reference to self 

	UFUNCTION(BlueprintCallable)
		void SetDamage(float DamageToSetTo);

	UFUNCTION(BlueprintCallable)
		void ChangeCooldownTime(float TimeToSetTo);

	UFUNCTION(BlueprintCallable)
		FORCEINLINE float GetCooldownTime() const { return CooldownTime; }
		
};
