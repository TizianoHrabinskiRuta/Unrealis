// a

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AIEnemyBase.h"
#include "TimeMagicComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNREALIS_API UTimeMagicComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UTimeMagicComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		TArray<AActor*> EnemiesToFreeze;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		bool InCooldown = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		float FreezeTime = 10.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		float CooldownTime = 5.f;

	UFUNCTION()
		void UnfreezeCallback();

	UFUNCTION()
		void CooldownCallback();

	FTimerHandle CooldownDelegate;

	FTimerHandle UnfreezeDelegate;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
		void FreezeEnemies();

	UFUNCTION(BlueprintCallable)
		FORCEINLINE void SetFreezeTime(float In) { FreezeTime = In; }

	UFUNCTION(BlueprintCallable)
		FORCEINLINE void SetCooldownTime(float In) { CooldownTime = In; }
};
