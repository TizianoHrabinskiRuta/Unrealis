// a


#include "EnemyEncounterManager.h"
#include "AIEnemyBase.h"
#include "SlimeBase.h"
#include "EnemyBaseComponent.h"
#include "EnemyController.h"
#include "Kismet/KismetMathLibrary.h"


AEnemyEncounterManager::AEnemyEncounterManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	EncounterTrigger = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("EncounterTrigger"));

	EncounterTrigger->SetupAttachment(RootComponent);
	
}

void AEnemyEncounterManager::BeginPlay()
{
	Super::BeginPlay();
	EncounterTrigger->OnComponentBeginOverlap.AddDynamic(this, &AEnemyEncounterManager::OnOverlapBegin);

	if (AutomaticallyCallVictory)
	{
		OnEncounterFinish();
		return;
	}

	if (PresetPatrolPoints.IsEmpty()) 
	{ 
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("No patrol points given for assignment @EnemyEncounterManager")); 
		CanInitiateEncounter = false;
		return; 
	}

	if (SpawnPoints.IsEmpty())
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("No spawn points to assign @EnemyEncounterManager"));
		CanInitiateEncounter = false;
		return;
	}

	if (ShouldHaveTimeLimit && TimeLimit == NULL) 
	{ 
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("No time assigned for time limit @EnemyEncounterManager")); 
		CanInitiateEncounter = false;
		return; 
	}

	if (NumberOfEnemiesToSpawn < MinimumEnemyKillCount)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("More enemies need to be killed than will spawn @EnemyEncounterManager"));
		CanInitiateEncounter = false;
		return;
	}

	for (auto h : PresetPatrolPoints) 
		if (h == nullptr) 
		{ 
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("An index in the PresetPatrolPoints array is empty. Either delete it or assign a patrol point to it @EnemyEncounterManager")); 
			CanInitiateEncounter = false; 
			return; 
		}


	if (SpawnOnPlay) { SpawnEnemies(); OnEncounterStart();	}

}

void AEnemyEncounterManager::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->ActorHasTag("PlayerTag") && !EncounterHasStarted) { SpawnEnemies(); EncounterHasStarted = true; OnEncounterStart(); }
}

void AEnemyEncounterManager::SpawnEnemies()
{
	if (!CanInitiateEncounter) return;
	if (EncounterHasStarted) return;

	EncounterHasStarted = true;


	for (int i = 0; i < NumberOfEnemiesToSpawn; i++)
	{

		if (UKismetMathLibrary::RandomBool())
		{
			if (Enemy1_IsSlimeBase)
			{
				if (!SpawnSlimeBase(Enemy1))
				{
					GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Failed to spawn @EnemyEncounterManager"));
					break;
				}
			}
			else
			{
				if (!SpawnEnemyBase(Enemy1)) 
				{
					GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Failed to spawn @EnemyEncounterManager"));
					break;
				}
			}
		}

		else
		{
			if (Enemy2_IsSlimeBase)
			{
				if (!SpawnSlimeBase(Enemy2)) 
				{
					GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Failed to spawn @EnemyEncounterManager"));
					break;
				}
			}
			else
			{
				if (!SpawnEnemyBase(Enemy2)) 
				{
					GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Failed to spawn @EnemyEncounterManager"));
					break;
				}
			}
		}
	}
}

FVector AEnemyEncounterManager::GetRandomSpawnPointLocation()
{
	int Random;
	
	do
	{
		 Random = UKismetMathLibrary::RandomIntegerInRange(0, SpawnPoints.Num() - 1);
	} while (Random == PreviousSpawnPointIndex);
	
	PreviousSpawnPointIndex = Random;

	return UKismetMathLibrary::TransformLocation(GetActorTransform(), SpawnPoints[Random]); 
}

TArray<AActor*> AEnemyEncounterManager::GenerateRandomPatrolPoints(int NumberOfPatrolPoints)
{
	TArray<AActor*> ReturningArray;


	int RandomNumber = 0;
	int PreviousNumber = -1;

	while (ReturningArray.Num() < NumberOfPatrolPoints)
	{
		RandomNumber = UKismetMathLibrary::RandomIntegerInRange(0, PresetPatrolPoints.Num() - 1);
		if (RandomNumber == PreviousNumber) continue;

		ReturningArray.Add(PresetPatrolPoints[RandomNumber]);
	}

	return ReturningArray;
}

bool AEnemyEncounterManager::SpawnSlimeBase(TSubclassOf<AActor> Reference)
{

	FActorSpawnParameters SpawnParams = FActorSpawnParameters();
	SpawnParams.bNoFail = true;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	ASlimeBase* SpawnedInstance = GetWorld()->SpawnActor<ASlimeBase>(Reference, GetRandomSpawnPointLocation(), FRotator(0, 0, 0), SpawnParams);
	if (!SpawnedInstance)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("There was an error spawning in SlimeBase @EnemyEncounterManager"));
		return false;
	}

	if (EnemiesAreInstantAggro)
	{
		SpawnedInstance->GetController<AEnemyController>()->GetBlackboard()->SetValueAsObject(TEXT("Target"), PlayerReference);
		SpawnedInstance->GetController<AEnemyController>()->GetBlackboard()->SetValueAsBool(TEXT("IsInstantAggro"), true);
		SpawnedInstance->SetPlayerReference(Cast<AActor>(PlayerReference));
	}

	
	SpawnedInstance->OverrideDefaultPatrolPoints(GenerateRandomPatrolPoints(2));
	SpawnedInstance->GetEnemyBase()->OnDeath.AddDynamic(this, &AEnemyEncounterManager::OnDeathCallback);

	return true;
}

bool AEnemyEncounterManager::SpawnEnemyBase(TSubclassOf<AActor> Reference)
{
	FActorSpawnParameters SpawnParams = FActorSpawnParameters();
	SpawnParams.bNoFail = true;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	AAIEnemyBase* SpawnedInstance = GetWorld()->SpawnActor<AAIEnemyBase>(Reference, GetRandomSpawnPointLocation(), FRotator(0, 0, 0), SpawnParams);
	if (!SpawnedInstance)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("There was an error spawning in AAIEnemyBase @EnemyEncounterManager"));
		return false;
	}

	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParams.ObjectFlags |= RF_Transient;

	AEnemyController* InstancedController = GetWorld()->SpawnActor<AEnemyController>(SpawnedInstance->GetActorLocation(), SpawnedInstance->GetActorRotation(), SpawnParams);

	if(InstancedController)
		InstancedController->Possess(SpawnedInstance);
	else GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("no controller for skellington"));

	if (EnemiesAreInstantAggro)
	{
		SpawnedInstance->GetController<AEnemyController>()->GetBlackboard()->SetValueAsObject(TEXT("Target"), PlayerReference);
		SpawnedInstance->GetController<AEnemyController>()->GetBlackboard()->SetValueAsBool(TEXT("IsInstantAggro"), true);
	}

	if (InstancedController) InstancedController->OverrideDefaultPatrolPoints(GenerateRandomPatrolPoints(2));
		else GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("No controller registered for instanced AAIEnemyBase subclass @EnemyEncounterManager"));
	
	SpawnedInstance->GetEnemyBase()->OnDeath.AddDynamic(this, &AEnemyEncounterManager::OnDeathCallback);

	return true;
}

void AEnemyEncounterManager::TimerCallback()
{
	FinishEncounter();
}

void AEnemyEncounterManager::FinishEncounter()
{
	OnEncounterFinish();
}

void AEnemyEncounterManager::OnEncounterFinish_Implementation()
{
}

void AEnemyEncounterManager::OnEncounterStart_Implementation()
{
}

void AEnemyEncounterManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

} 