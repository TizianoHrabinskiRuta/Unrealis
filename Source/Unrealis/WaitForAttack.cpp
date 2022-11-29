// a


#include "WaitForAttack.h"
#include "EnemyController.h"

EBTNodeResult::Type UWaitForAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	this->bNotifyTick = true;

	OwnerRef = Cast<AEnemyController>(OwnerComp.GetAIOwner())->GetControllerOwner();
	OwnerRef->OnAttackEnd.AddDynamic(this, &UWaitForAttack::CallbackRecipient);

	return EBTNodeResult::InProgress;
}

void UWaitForAttack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	if (HasEnded)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		HasEnded = false;
	}
}
