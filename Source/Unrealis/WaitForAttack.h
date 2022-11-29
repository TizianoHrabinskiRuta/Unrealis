// a

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "AIEnemyBase.h"
#include "WaitForAttack.generated.h"

/**
 * 
 */
UCLASS()
class UNREALIS_API UWaitForAttack : public UBTTaskNode
{
	GENERATED_BODY()
	
		virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;


	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds);

protected:

	UPROPERTY()
		bool HasEnded = false;

	UFUNCTION()
		void CallbackRecipient()
	{
		HasEnded = true;
	}


	UPROPERTY()
		AAIEnemyBase* OwnerRef;
};
