// a

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TargetPointBase.h"
#include "EnemyEncounterManager.generated.h"

UCLASS()
class UNREALIS_API AEnemyEncounterManager : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AEnemyEncounterManager();

	UPROPERTY(BlueprintReadWrite, EditInstanceOnly, meta = (ToolTip = "What patrol points can be assigned to the spawned enemies"))
		TArray<ATargetPointBase*> PresetPatrolPoints;

	UPROPERTY(BlueprintReadWrite, EditInstanceOnly)
		TSubclassOf<AActor> Enemy1;

	UPROPERTY(EditInstanceOnly, meta = (DisplayName = "Is SlimeBase", ToolTip = "Is this enemy an instance of SlimeBase"))
		bool Enemy1_IsSlimeBase = false;

	UPROPERTY(BlueprintReadWrite, EditInstanceOnly)
		TSubclassOf<AActor> Enemy2;

	UPROPERTY(EditInstanceOnly, meta = (DisplayName = "Is Slimebase", ToolTip = "Is this enemy an instance of SlimeBase"))
		bool Enemy2_IsSlimeBase = false;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = SpawnPoints, meta = (ToolTip = "Ensure the spawn point has enough height to be able to spawn the enemy without clipping through the ground", MakeEditWidget = true))
		FVector SpawnPoint1;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = SpawnPoints, meta = (ToolTip = "Ensure the spawn point has enough height to be able to spawn the enemy without clipping through the ground", MakeEditWidget = true))
		FVector SpawnPoint2;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = SpawnPoints, meta = (ToolTip = "Ensure the spawn point has enough height to be able to spawn the enemy without clipping through the ground", MakeEditWidget = true))
		FVector SpawnPoint3;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = SpawnPoints, meta = (ToolTip = "Ensure the spawn point has enough height to be able to spawn the enemy without clipping through the ground", MakeEditWidget = true))
		FVector SpawnPoint4;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EncounterTrigger)
		UStaticMeshComponent* EncounterTrigger;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool ShouldHaveTimeLimit = false;

	UPROPERTY(BlueprintReadWrite, EditInstanceOnly, meta = (EditCondition = "ShouldHaveTimeLimit", ToolTip = "How long before the encounter is finished, in seconds."))
		int TimeLimit = NULL;
	
	UPROPERTY(EditAnywhere)
		bool SpawnOnPlay = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ToolTip = "This is for debugging purposes only"))
		bool AutomaticallyCallVictory = false;	

	UPROPERTY(BlueprintReadWrite, EditInstanceOnly)
		int NumberOfEnemiesToSpawn = 4;

	UPROPERTY(BlueprintReadWrite, EditInstanceOnly, meta = (ToolTip = "How many enemies the player has to kill before the encounter is considered to be won or finished"))
		int MinimumEnemyKillCount = NumberOfEnemiesToSpawn;		



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
			bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		TArray<AActor*> GenerateRandomPatrolPoints(int NumberOfPatrolPoints);

	UFUNCTION()
		FVector GetRandomSpawnPointLocation();

	UFUNCTION()
		void SpawnEnemies();

	UFUNCTION()
		void FinishEncounter();

	UFUNCTION()
		void TimerCallback(); // The function thats called if an encounter has a timer and that timer expires.

	UFUNCTION()
		void OnDeathCallback()
	{
		KilledEnemies += 1;
		if (KilledEnemies >= MinimumEnemyKillCount) FinishEncounter();
	}

	UFUNCTION()
		bool SpawnSlimeBase(TSubclassOf<AActor> Reference);

	UFUNCTION()
		bool SpawnEnemyBase(TSubclassOf<AActor> Reference);

	UFUNCTION(BlueprintNativeEvent)
		void OnEncounterFinish();

	UFUNCTION(BlueprintNativeEvent)
		void OnEncounterStart();

	UPROPERTY()
		FTimerHandle EncounterTimerHandle;

	UPROPERTY()
		TArray<AActor*> SpawnedEnemies;

	UPROPERTY()
		int KilledEnemies = 0;

	UPROPERTY()
		bool EncounterHasStarted = false;

	UPROPERTY()
		bool CanInitiateEncounter = true;

	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};


