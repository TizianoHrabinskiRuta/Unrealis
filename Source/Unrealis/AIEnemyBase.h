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

public:
	// Sets default values for this character's properties
	AAIEnemyBase();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UBehaviorTree* Tree;	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintNativeEvent)
		void OnDeathCallback();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UEnemyBaseComponent* EnemyBaseComponent;	

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
	FORCEINLINE UEnemyBaseComponent* GetEnemyBase() const { return EnemyBaseComponent; }
};
