// a

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "FireballComponent.h"
#include "DebuggingPawn.generated.h"

UCLASS()
class UNREALIS_API ADebuggingPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ADebuggingPawn();

	UPROPERTY(EditAnywhere)
		float MovementSpeed;

	UPROPERTY(EditAnywhere)
		float RotationSensitivity;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* StaticMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UCapsuleComponent* CapsuleCollider;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UCapsuleComponent* CapsuleTrigger;



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveForwards(float AxisValue);

	void MoveSideways(float AxisValue);

	void Rotate(float AxisValue);

	UFUNCTION(BlueprintNativeEvent)
		void AttackOne();

};
