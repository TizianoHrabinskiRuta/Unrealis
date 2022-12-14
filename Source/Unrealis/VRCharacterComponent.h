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

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FHasHealedDelegate, float, InHealth);

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FAttackEventDelegate);


public:
	// Sets default values for this component's properties
	UVRCharacterComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION()
		void Attack1();

	UFUNCTION()
		void CallElementChangeEvent();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		float Health;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		float MaxHealth = 150.f;

	UPROPERTY()
		class UInputComponent* PlayerInputComponent;

	UPROPERTY()
		float DefenseMultiplier = 1.f; // The lower this is, the higher the defense
	
public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
		void TakeDamage(float Damage);

	UFUNCTION(BlueprintCallable)
		void HealPlayer(float InHealth);

	UFUNCTION(BlueprintCallable)
		void IncreaseDefense(float InDefense) { DefenseMultiplier -= InDefense; } // Subtracts DefenseMultiplier against InDefense. Base DefenseMultiplier is 1, so InDefense should be a small positive number, since defense is a multiplier.

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

	UPROPERTY(BlueprintAssignable)
		FHasHealedDelegate OnHeal;
};
