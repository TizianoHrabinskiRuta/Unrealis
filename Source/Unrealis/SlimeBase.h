// a

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "EnemyBaseComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Perception/PawnSensingComponent.h"
#include "SlimeBase.generated.h"

UCLASS()
class UNREALIS_API ASlimeBase : public APawn
{
	GENERATED_BODY()

		DECLARE_DYNAMIC_MULTICAST_DELEGATE(FRotationUpdatedDelegate);
		DECLARE_DYNAMIC_MULTICAST_DELEGATE(FInitiateJumpDelegate);
		DECLARE_DYNAMIC_MULTICAST_DELEGATE(FHasBeenGroundedDelegate);


public:
	// Sets default values for this pawn's properties
	ASlimeBase();

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
		void OnPlayerCaught(APawn* CaughtPawn);

	UFUNCTION()
		void CheckForGroundHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

	UPROPERTY()
		TArray<AActor*> OverlappingActors;
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintNativeEvent)
		void ExecuteAttack1();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
		FORCEINLINE UEnemyBaseComponent* GetEnemyBase() const { return HealthComponent; }

	UFUNCTION(BlueprintCallable)
		FORCEINLINE bool IsGrounded() const { return bIsGrounded; };

	UFUNCTION(BlueprintNativeEvent)
		void FreezeAnimations();

	UFUNCTION(BlueprintNativeEvent)
		void UnfreezeAnimations();

	UFUNCTION(BlueprintNativeEvent)
		void RequestJump();

	UFUNCTION(BlueprintNativeEvent)
		void OnGroundEvent();

	UFUNCTION(BlueprintCallable)
		void FireJumpRequest() { OnJumpRequest.Broadcast(); }

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI)
		TArray<AActor*> PatrolPoints;

	UPROPERTY(BlueprintAssignable)
		FHasBeenGroundedDelegate OnGround;

	UPROPERTY(BlueprintAssignable)
		FInitiateJumpDelegate OnJumpRequest;

};
