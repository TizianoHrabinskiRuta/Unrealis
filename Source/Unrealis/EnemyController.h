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

		UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class  UBehaviorTreeComponent* BehaviorTreeComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBlackboardComponent* BlackboardComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		FName LocationToGoKey;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		FName PlayerKey;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TArray<AActor*> PatrolPoints;

	UFUNCTION()
	virtual void OnPossess(APawn* PossessedPawn) override;


public:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 CurrentPatrolPoint = 0;

	UFUNCTION()
	void SetPlayerCaught(APawn* CaughtPawn);

	FAttack1Call OnAttack1Call;

	UFUNCTION()
		void CallExecuteAttack1();

	FORCEINLINE UBlackboardComponent* GetBlackboard() const { return BlackboardComp; }
	FORCEINLINE TArray<AActor*> GetPatrolPoints() const { return PatrolPoints; }
	
}; 
