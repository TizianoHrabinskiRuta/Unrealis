// a

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/InputComponent.h"
#include "VRCharacterComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNREALIS_API UVRCharacterComponent : public UActorComponent
{
	GENERATED_BODY()

		DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDiedDelegate);

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FHasTakenDamageDelegate, float, DamageTaken);

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FAttackEventDelegate);


public:
	// Sets default values for this component's properties
	UVRCharacterComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		float Health;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		float MaxHealth = 150.f;

	UPROPERTY()
		class UInputComponent* PlayerInputComponent;

	UFUNCTION()
		void Attack1();

	UFUNCTION()
		void CallElementChangeEvent();

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
		void TakeDamage(float Damage);

	UFUNCTION(BlueprintCallable)
		FORCEINLINE float GetHealth() const { return Health; }

	UFUNCTION(BlueprintCallable)
		FORCEINLINE float GetMaxHealth() const { return MaxHealth; }

	UFUNCTION(BlueprintCallable)
		FORCEINLINE void SetMaxHealth(float In) { MaxHealth = In; }

	UPROPERTY(BlueprintAssignable)
		FAttackEventDelegate Attack1Event;

	UPROPERTY(BlueprintAssignable)
		FAttackEventDelegate OnElementChange;

	UPROPERTY(BlueprintAssignable)
		FDiedDelegate OnDeath;

	UPROPERTY(BlueprintAssignable)
		FHasTakenDamageDelegate OnDamaged;		
};
