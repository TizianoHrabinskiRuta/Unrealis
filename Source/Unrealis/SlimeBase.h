// a

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "EnemyBaseComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Perception/PawnSensingComponent.h"
#include "SlimeBase.generated.h"





//make a base class that would represent an item in the world, and force that to be passed to the function, which will spawn them in the world

UCLASS()
class UNREALIS_API ASlimeBase : public APawn
{
	GENERATED_BODY()

		DECLARE_DYNAMIC_MULTICAST_DELEGATE(FRotationUpdatedDelegate);
		DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FInitiateJumpDelegate, AActor*, Caller);
		DECLARE_DYNAMIC_MULTICAST_DELEGATE(FHasBeenGroundedDelegate);
		
		
public:
	// Sets default values for this pawn's properties
	ASlimeBase();

	UFUNCTION(BlueprintCallable)
		void OverrideDefaultPatrolPoints(TArray<AActor*>InPatrolPoints);

	UFUNCTION()
		FORCEINLINE void SetPlayerReference(AActor* InPlayerRef)
	{
		CaughtPlayer = InPlayerRef;
	}


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UBehaviorTree* Tree;

	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintNativeEvent)
		void OnDeathCallback();	

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UEnemyBaseComponent* HealthComponent;	

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UPawnSensingComponent* PawnSensor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UStaticMeshComponent* Hitbox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class USkeletalMeshComponent* CharacterMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		bool bIsGrounded = true;

private:

	UFUNCTION()
		AActor* GetCurrentTarget();

	UFUNCTION()
		bool IsPlayerTheCurrentTarget();

	UFUNCTION()
		bool HasReachedDestination();

	UFUNCTION()
		void OnPlayerCaught(APawn* CaughtPawn);

	UFUNCTION()
		void CheckForGroundHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);		

	UPROPERTY()
		AActor* CaughtPlayer;

	UPROPERTY()
		int SelectedPatrolPointIndex = 0;

	UPROPERTY(EditAnywhere, Category = AI)
		float DistanceThreshold = 200.f;

	UPROPERTY(EditAnywhere, meta = (ToolTip = "How much force is applied for the physics calculation of the jump"))
		float ForwardsForceToApply = 3500.f;

	UPROPERTY(EditAnywhere, meta = (ToolTip = "How much force is applied for the physics calculation of the jump"))
		float UpwardsForceToApply = 10000.f;

	
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
		FORCEINLINE AActor* GetCurrentPatrolPoint() const { return PatrolPoints[SelectedPatrolPointIndex]; }

	UFUNCTION(BlueprintCallable)
		FORCEINLINE UEnemyBaseComponent* GetEnemyBase() const { return HealthComponent; }

	UFUNCTION(BlueprintCallable)
		FORCEINLINE bool IsGrounded() const { return bIsGrounded; };

	UFUNCTION(BlueprintNativeEvent)
		void ExecuteAttack1();		

	UFUNCTION(BlueprintNativeEvent)
		void FreezeAnimations();

	UFUNCTION(BlueprintNativeEvent)
		void UnfreezeAnimations();

	UFUNCTION(BlueprintNativeEvent)
		void RequestJump();

	UFUNCTION(BlueprintNativeEvent)
		void OnGroundEvent2();

	UFUNCTION(BlueprintCallable)
		void FireJumpRequest();

	UFUNCTION()
		void SwitchPatrolPoint();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI)
		TArray<AActor*> PatrolPoints;

	UPROPERTY(BlueprintAssignable)
		FHasBeenGroundedDelegate OnGround;

	UPROPERTY(BlueprintAssignable)
		FInitiateJumpDelegate OnJumpRequest;

};
