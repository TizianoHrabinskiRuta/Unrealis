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

void AEnemyController::OverrideDefaultPatrolPoints(TArray<AActor*> InPatrolPoints)
{

	if(!InternalPatrolPoints.IsEmpty())
		InternalPatrolPoints.Empty();

	for (auto h : InPatrolPoints)
	{
		InternalPatrolPoints.Add(h);
	}
}

void AEnemyController::OnPossess(APawn* PossessedPawn)
{
	Super::OnPossess(PossessedPawn);

	//add message on possess

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
		
		SlimeOwnerRef = Cast<ASlimeBase>(PossessedPawn);
		if (SlimeOwnerRef)
		{
			BlackboardComp->InitializeBlackboard(*(SlimeOwnerRef->Tree->BlackboardAsset));

			InternalPatrolPoints = SlimeOwnerRef->PatrolPoints;

			BehaviorTreeComp->StartTree(*SlimeOwnerRef->Tree);

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
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Called @EC"));
	OnAttack1Call.Broadcast();
}

