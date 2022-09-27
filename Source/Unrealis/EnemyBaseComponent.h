// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EnemyBaseComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNREALIS_API UEnemyBaseComponent : public UActorComponent
{
	GENERATED_BODY()

		DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDiedDelegate);

		DECLARE_DYNAMIC_MULTICAST_DELEGATE(FHasTakenDamageDelegate); 

public:	
	// Sets default values for this component's properties
	UEnemyBaseComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		float Health = 150.f;

private:

	UFUNCTION()
	void CheckForDeath();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
		void TakeDamage(float Damage);

	UFUNCTION(BlueprintCallable)
		FORCEINLINE float GetHealth() const { return Health; }

	UFUNCTION(BlueprintNativeEvent)
		void HasDied();

	UPROPERTY(BlueprintAssignable)
	FDiedDelegate OnDeath;

	UPROPERTY(BlueprintAssignable)
		FHasTakenDamageDelegate OnDamaged;

};
