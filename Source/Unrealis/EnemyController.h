// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "EnemyController.generated.h"

/**
 * 
 */
UCLASS()
class UNREALIS_API AEnemyController : public AAIController
{
	GENERATED_BODY()

		AEnemyController();

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FAttack1Call);


protected:

	UFUNCTION()
		virtual void OnPossess(APawn* PossessedPawn) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UBehaviorTreeComponent* BehaviorTreeComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UBlackboardComponent* BlackboardComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		FName LocationToGoKey;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		FName PlayerKey;	

	UPROPERTY()
		class AAIEnemyBase* OwnerRef;

	UPROPERTY()
		class ASlimeBase* SlimeOwnerRef;

public:

	UFUNCTION()
		void SetPlayerCaught(APawn* CaughtPawn);

	UFUNCTION(BlueprintCallable)
		void OverrideDefaultPatrolPoints(TArray<AActor*> InPatrolPoints);

	UFUNCTION()
		FORCEINLINE UBlackboardComponent* GetBlackboard() const { return BlackboardComp; }

	UFUNCTION()
		FORCEINLINE TArray<AActor*> GetPatrolPoints() const { return InternalPatrolPoints; }

	UFUNCTION()
		void CallExecuteAttack1();

	UFUNCTION()
		FORCEINLINE AAIEnemyBase* GetControllerOwner() const { return OwnerRef; }

	UFUNCTION()
		FORCEINLINE ASlimeBase* GetSlimeControllerOwner() const { return SlimeOwnerRef; }

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		TArray<AActor*> InternalPatrolPoints;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		int32 CurrentPatrolPoint = 0;

	FAttack1Call OnAttack1Call;

}; 
