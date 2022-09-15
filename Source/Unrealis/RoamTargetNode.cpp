// Fill out your copyright notice in the Description page of Project Settings.


#include "RoamTargetNode.h"
#include "TargetPointBase.h"
#include "EnemyController.h"

EBTNodeResult::Type URoamTargetNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	AEnemyController* Controller = Cast<AEnemyController>(OwnerComp.GetAIOwner()); // Get the controller from relevant AI character / pawn

	if (Controller) // if found
	{
		UBlackboardComponent* BlackboardComp = Controller->GetBlackboardComponent();
		TArray<AActor*> AvailablePatrolPoints = Controller->GetPatrolPoints(); //Get all the target points relevant to the AI, stored in its controller

		ATargetPointBase* CurrentPoint = Cast<ATargetPointBase>(BlackboardComp->GetValueAsObject("LocationToGo")); // Gets the Key in the blackboard that holds the reference to the current Target point
		
		ATargetPointBase* NextPatrolPoint = nullptr;


		if (Controller->CurrentPatrolPoint != AvailablePatrolPoints.Num() - 1) // If it hasnt already cycled through all the target points
		{
			NextPatrolPoint = Cast<ATargetPointBase>(AvailablePatrolPoints[++Controller->CurrentPatrolPoint]); // Gets the reference to the next target point stored in the TArray<AActor*>
		}

		else // If it has cycled through all Target points, set the current patrol point to the beginning
		{
			NextPatrolPoint = Cast<ATargetPointBase>(AvailablePatrolPoints[0]);
			Controller->CurrentPatrolPoint = 0;
		}


		BlackboardComp->SetValueAsObject("LocationToGo", NextPatrolPoint); // Changes the key in the blackboard to the reference of the found to be next target point


		return EBTNodeResult::Succeeded; // lets the logic handler know the code hasnt fucked up 
	}
	return EBTNodeResult::Failed; // lets the logic handler know the code has fucked up

}