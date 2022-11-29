// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyBaseComponent.h"
#include "Perception/PawnSensingComponent.h"
#include "AIEnemyBase.generated.h"

UCLASS()
class UNREALIS_API AAIEnemyBase : public ACharacter
{
	GENERATED_BODY()

		DECLARE_DYNAMIC_MULTICAST_DELEGATE(FAttackAnimationEndedDelegate);

public:
	// Sets default values for this character's properties
	AAIEnemyBase();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UBehaviorTree* Tree;	

	UPROPERTY()
		FAttackAnimationEndedDelegate OnAttackEnd;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintNativeEvent)
		void OnDeathCallback();

	UFUNCTION(BlueprintCallable)
		FORCEINLINE void CallAttackEndDelegate()
	{
		OnAttackEnd.Broadcast();
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UEnemyBaseComponent* HealthComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UPawnSensingComponent* PawnSensor;

private: 

	UFUNCTION()
		void OnPlayerCaught(APawn* CaughtPawn);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;	

	UFUNCTION(BlueprintNativeEvent)
		void ExecuteAttack1();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
	FORCEINLINE UEnemyBaseComponent* GetEnemyBase() const { return HealthComponent; }

	UFUNCTION(BlueprintNativeEvent)
		void FreezeAnimations();

	UFUNCTION(BlueprintNativeEvent)
		void UnfreezeAnimations();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI)
		TArray<AActor*> PatrolPoints;

};
