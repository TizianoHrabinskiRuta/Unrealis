// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BehaviorTree.h"
#include "TargetPointBase.h"
#include "SlimeBase.h"
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

	OwnerRef = Cast<AAIEnemyBase>(PossessedPawn);
	
	if (OwnerRef)
	{
		if (OwnerRef->Tree->BlackboardAsset)
		{
			BlackboardComp->InitializeBlackboard(*(OwnerRef->Tree->BlackboardAsset));

			InternalPatrolPoints = OwnerRef->PatrolPoints;

			BehaviorTreeComp->StartTree(*OwnerRef->Tree);
		}
	}
	else
	{
		
		ASlimeBase* _OwnerRef = Cast<ASlimeBase>(PossessedPawn);
		if (_OwnerRef)
		{
			BlackboardComp->InitializeBlackboard(*(_OwnerRef->Tree->BlackboardAsset));

			InternalPatrolPoints = _OwnerRef->PatrolPoints;

			BehaviorTreeComp->StartTree(*_OwnerRef->Tree);

		} else {
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT(":( @EC"));
		}
	}
}

void AEnemyController::SetPlayerCaught(APawn* CaughtPawn)
{

	if (BlackboardComp)
	{
		BlackboardComp->SetValueAsObject(PlayerKey, CaughtPawn); // if the player was sensed, make the key in the blackboard have a reference to the relevant player
		BlackboardComp->SetValueAsVector(TEXT("TargetLocation"), CaughtPawn->GetActorLocation());
	}
}

void AEnemyController::CallExecuteAttack1()
{
	OnAttack1Call.Broadcast();
}

