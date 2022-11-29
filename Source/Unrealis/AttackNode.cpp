// a


#include "AttackNode.h"
#include "AIEnemyBase.h"
#include "EngineGlobals.h"
#include "EnemyController.h"

 EBTNodeResult::Type UAttackNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
 {
	AEnemyController* Enemy = Cast<AEnemyController>(OwnerComp.GetAIOwner());
	


	if (Enemy)
	{
		Enemy->GetPawn<AAIEnemyBase>()->ExecuteAttack1();
		
		return EBTNodeResult::Succeeded;
	}

	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Failed to execute attack node"));
		return EBTNodeResult::Failed;
	}
 }
