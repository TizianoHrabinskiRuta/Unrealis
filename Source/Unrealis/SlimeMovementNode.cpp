

// a


#include "SlimeMovementNode.h"
#include "SlimeBase.h"
#include "AIController.h"
#include "EnemyController.h"
#include "AIEnemyBase.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType.h"




EBTNodeResult::Type USlimeMovementNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	AAIController* OwnerController = OwnerComp.GetAIOwner();

	OwnerActor = Cast<AActor>(Cast<AEnemyController>(OwnerController)->GetSlimeControllerOwner()); 
	
	UBlackboardComponent* Blackboard = OwnerController->GetBlackboardComponent();
	
    Target = Cast<AActor>(Blackboard->GetValueAsObject(TargetKey.SelectedKeyName));

	StoredTreeReference = &OwnerComp;
	
	if (!OwnerActor) { GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("No owner?")); return EBTNodeResult::Failed; }
	if (!Target) { GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("No key selected for target, or key is empty @SlimeMovementNode"));	return EBTNodeResult::Failed; }
			
	ASlimeBase* SlimeOwner = Cast<ASlimeBase>(OwnerActor);
	if (SlimeOwner) SlimeOwner->OnJumpRequest.AddDynamic(this, &USlimeMovementNode::OnJumpRequest);
	else return EBTNodeResult::Failed;

	if (HasReachedDestination) return EBTNodeResult::Succeeded;
	return EBTNodeResult::InProgress;
}



void USlimeMovementNode::TimerCallback()
{
	BounceDebounce = false;
}

void USlimeMovementNode::OnJumpRequest(AActor* Callee)
{
	if (BounceDebounce) return;
	BounceDebounce = true;

	if (FVector::Distance(Callee->GetActorLocation(), Callee->GetActorLocation()) <= DistanceThreshold)
	{
		FinishLatentTask(*StoredTreeReference, EBTNodeResult::Succeeded);
	}

	Callee->SetActorRotation(UKismetMathLibrary::FindLookAtRotation(OwnerActor->GetActorLocation(), Target->GetActorLocation()));

	OwnerPrimitive = Cast<UPrimitiveComponent>(Callee->GetRootComponent());

	
	FVector CalculatedForwardsForceToApply = FVector(OwnerActor->GetActorForwardVector() * ForwardsForceToApply);
	FVector CalculatedUpwardsForceToApply = FVector(0.f, 0.f, UpwardsForceToApply);

	OwnerPrimitive->AddImpulse(CalculatedUpwardsForceToApply);
	OwnerPrimitive->AddImpulse(CalculatedForwardsForceToApply);
	
	GetWorld()->GetTimerManager().SetTimer(DebounceHandle, this, &USlimeMovementNode::TimerCallback, 0.05f, false);

}

