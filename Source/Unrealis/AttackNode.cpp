// a


#include "AttackNode.h"
#include "AIEnemyBase.h"
#include "EnemyController.h"

 EBTNodeResult::Type UAttackNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
 {
	AEnemyController* Enemy = Cast<AEnemyController>(OwnerComp.GetAIOwner());


	if (Enemy)
	{
		Enemy->CallExecuteAttack1();
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Executed attack node"));


		return EBTNodeResult::Succeeded;
	}

	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Failed to execute attack node"));
		return EBTNodeResult::Failed;
	}
 }
