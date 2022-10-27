// a

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "SlimeBase.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "SlimeMovementNode.generated.h"

/**
 * Movement node for the slime enemy. Should only be used for the slime enemy, and used in the same fashion as the MoveTo node.
 */
UCLASS()
class UNREALIS_API USlimeMovementNode : public UBTTaskNode
{
	GENERATED_BODY()

		virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "TargetKey"))
		FBlackboardKeySelector TargetKey;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ToolTip = "The owner of this node instance. Please set so this doesnt break"))
		FBlackboardKeySelector OwnerKey;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Acceptable distance to target", ToolTip = "How far away the owner can be to the target before the node calls success. I suggest you exaggerate it by around 30 units, since the calculation to target is a bit scuffed for some reason."))
		float DistanceThreshold;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ToolTip = "How much force is applied for the physics calculation of the jump"))
		float ForwardsForceToApply = 150.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ToolTip = "How much force is applied for the physics calculation of the jump"))
		float UpwardsForceToApply = 150.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ToolTip = "Should debugging symbols display at runtime"))
		bool DisplayDebuggingSymbols = false;

	UFUNCTION()
		void OnJumpRequest(AActor* Callee);


private:

	UFUNCTION()
		void TimerCallback();
	
	UPROPERTY()
		FRotator FoundLookAtRotation;

	UPROPERTY()
		FTimerHandle DebounceHandle;

	UPROPERTY()
		AActor* Target;

	UPROPERTY()
		AActor* OwnerActor;

	UPROPERTY()
		UPrimitiveComponent* OwnerPrimitive;

	UPROPERTY()
		UBehaviorTreeComponent* StoredTreeReference;

	UPROPERTY()
		bool HasReachedDestination = false;

	UPROPERTY()
		bool BounceDebounce = false;

	UPROPERTY()
		int FrameBuffer = 10;

	UPROPERTY()
		int TranscurredFrames = 0;




};
