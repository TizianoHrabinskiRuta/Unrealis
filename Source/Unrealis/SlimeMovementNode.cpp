

// a


#include "SlimeMovementNode.h"
#include "SlimeBase.h"
#include "AIController.h"
#include "EnemyController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType.h"




EBTNodeResult::Type USlimeMovementNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	bNotifyTick = true;
	AAIController* OwnerController = OwnerComp.GetAIOwner();
	OwnerActor = OwnerController->GetPawn();

	UBlackboardComponent* Blackboard = OwnerController->GetBlackboardComponent();
	
    Target = Cast<AActor>(Blackboard->GetValueAsObject(TargetKey.SelectedKeyName));
    OwnerPrimitive = Cast<UPrimitiveComponent>(OwnerActor->GetRootComponent());
	
	if (!OwnerActor) { GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("No owner?")); return EBTNodeResult::Failed; }
	if (!OwnerPrimitive) { GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("No primitive?")); return EBTNodeResult::Failed; }
	if (!Target) { GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("No key selected for target, or key is empty @SlimeMovementNode"));	return EBTNodeResult::Failed; }
			
	ASlimeBase* SlimeOwner = Cast<ASlimeBase>(OwnerActor);
	if (SlimeOwner) SlimeOwner->OnGround.AddDynamic(this, &USlimeMovementNode::OnGroundCallback);
	else return EBTNodeResult::Failed;

	if (HasReachedDestination) return EBTNodeResult::Succeeded;
	return EBTNodeResult::InProgress;
}


void USlimeMovementNode::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	if (FVector::Distance(OwnerActor->GetActorLocation(), Target->GetActorLocation()) <= DistanceThreshold)
	{
		if(DisplayDebuggingSymbols)
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Exited SMN"));
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}

	if(FrameBuffer > TranscurredFrames)
		TranscurredFrames++;
	
	if(DisplayDebuggingSymbols)
		UE_LOG(LogTemp, Warning, TEXT("%f"), FVector::Distance(OwnerActor->GetActorLocation(), Target->GetActorLocation()));

}


void USlimeMovementNode::OnGroundCallback()
{
	if (FrameBuffer > TranscurredFrames) return; // Guard clause so it doesnt jump twice in quick succession

	OwnerActor->SetActorRotation(UKismetMathLibrary::FindLookAtRotation(OwnerActor->GetActorLocation(), Target->GetActorLocation()));

	if(DisplayDebuggingSymbols)
		UE_LOG(LogTemp, Warning, TEXT("%f"), FVector::Distance(OwnerActor->GetActorLocation(), Target->GetActorLocation()));

	FVector CalculatedForwardsForceToApply = FVector(OwnerActor->GetActorForwardVector() * ForwardsForceToApply);
	FVector CalculatedUpwardsForceToApply = FVector(0.f, 0.f, UpwardsForceToApply);

	OwnerPrimitive->AddImpulse(CalculatedUpwardsForceToApply);
	OwnerPrimitive->AddImpulse(CalculatedForwardsForceToApply);
	
	TranscurredFrames = 0;

}

/*
FVector CalculatedForwardForce = FVector(ForceToApply);
	ASlimeBase* SlimeOwner = Cast<ASlimeBase>(OwnerActor);

	FoundLookAtRotation = UKismetMathLibrary::FindLookAtRotation(OwnerActor->GetActorLocation(), Target->GetActorLocation());
	OwnerActor->SetActorRotation(FoundLookAtRotation);
	OwnerPrimitive->AddImpulse(CalculatedForwardForce);



	if (FVector::Distance(OwnerActor->GetActorLocation(), Target->GetActorLocation()) <= DistanceThreshold) return EBTNodeResult::Succeeded;
	else return EBTNodeResult::InProgress;
*/