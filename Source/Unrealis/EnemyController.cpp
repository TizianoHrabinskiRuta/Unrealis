// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BehaviorTree.h"
#include "TargetPointBase.h"
#include "AIEnemyBase.h"


AEnemyController::AEnemyController()
{
	BehaviorTreeComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComponent"));
	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComponent"));

	LocationToGoKey = "LocationToGo";
	PlayerKey = "Target";

	CurrentPatrolPoint = 0;
}

void AEnemyController::OnPossess(APawn* PossessedPawn)
{
	Super::OnPossess(PossessedPawn);

	AAIEnemyBase* Enemy = Cast<AAIEnemyBase>(PossessedPawn);

	if (Enemy)
	{
		if (Enemy->Tree->BlackboardAsset)
		{
			BlackboardComp->InitializeBlackboard(*(Enemy->Tree->BlackboardAsset));
		}


		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATargetPointBase::StaticClass(), PatrolPoints);

		BehaviorTreeComp->StartTree(*Enemy->Tree);


	}
}

void AEnemyController::SetPlayerCaught(APawn* CaughtPawn)
{

	if (BlackboardComp)
	{
		BlackboardComp->SetValueAsObject(PlayerKey, CaughtPawn); // if the player was sensed, make the key in the blackboard have a reference to the relevant player
	}
}

