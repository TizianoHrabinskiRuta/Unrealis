// a


#include "EnemyEncounterManager.h"
#include "AIEnemyBase.h"
#include "SlimeBase.h"
#include "EnemyBaseComponent.h"
#include "EnemyController.h"
#include "Kismet/KismetMathLibrary.h"


// Sets default values
AEnemyEncounterManager::AEnemyEncounterManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	SpawnPoint1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SpawnPoint1"));
	SpawnPoint2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SpawnPoint2"));
	SpawnPoint3 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SpawnPoint3")); 
	SpawnPoint4 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SpawnPoint4"));

	EncounterTrigger = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("EncounterTrigger"));

	EncounterTrigger->SetupAttachment(RootComponent);
	SpawnPoint1->SetupAttachment(RootComponent);
	SpawnPoint2->SetupAttachment(RootComponent);
	SpawnPoint3->SetupAttachment(RootComponent);
	SpawnPoint4->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AEnemyEncounterManager::BeginPlay()
{
	Super::BeginPlay();
	EncounterTrigger->OnComponentBeginOverlap.AddDynamic(this, &AEnemyEncounterManager::OnOverlapBegin);

	if (PresetPatrolPoints.IsEmpty()) 
	{ 
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("No patrol points given for assignment @EnemyEncounterManager")); 
		CanInitiateEncounter = false;
		return; 
	}

	if (ShouldHaveTimeLimit && TimeLimit == NULL) 
	{ 
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("No time assigned for time limit @EnemyEncounterManager")); 
		CanInitiateEncounter = false;
		return; 
	}


	if (SpawnOnPlay)SpawnEnemies();

}

// Called every frame
void AEnemyEncounterManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnemyEncounterManager::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->ActorHasTag("PlayerTag") && !EncounterHasStarted) { SpawnEnemies(); EncounterHasStarted = true; }
}

TArray<AActor*> AEnemyEncounterManager::GenerateRandomPatrolPoints(int NumberOfPatrolPoints)
{
	TArray<AActor*> ReturningArray;


	int RandomNumber = 0;

	for (int i = 0; i < NumberOfPatrolPoints; i++)
	{
		RandomNumber = UKismetMathLibrary::RandomIntegerInRange(0, PresetPatrolPoints.Num() - 1);

		ReturningArray.Add(PresetPatrolPoints[RandomNumber]);
	}

	return ReturningArray;
}

FVector AEnemyEncounterManager::GetRandomSpawnPointLocation()
{
	int Random = UKismetMathLibrary::RandomIntegerInRange(1, 4);
	FVector ReturningVector = FVector();

	switch (Random)
	{
		case 1:
			ReturningVector = SpawnPoint1->GetComponentLocation();
			break;

		case 2:
			ReturningVector = SpawnPoint2->GetComponentLocation();
			break;

		case 3:
			ReturningVector = SpawnPoint3->GetComponentLocation();
			break;

		case 4:
			ReturningVector = SpawnPoint4->GetComponentLocation();
			break;
	}


	return ReturningVector;
}

bool AEnemyEncounterManager::SpawnSlimeBase(TSubclassOf<AActor> Reference)
{
	FActorSpawnParameters SpawnParams = FActorSpawnParameters();
	SpawnParams.bNoFail = true;

	ASlimeBase* SpawnedInstance = GetWorld()->SpawnActor<ASlimeBase>(Reference, GetRandomSpawnPointLocation(), FRotator(0, 0, 0), SpawnParams);
	if (!SpawnedInstance)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("There was an error spawning in SlimeBase @EnemyEncounterManager"));
		return false;
	}

	SpawnedInstance->OverrideDefaultPatrolPoints(GenerateRandomPatrolPoints(2));
	SpawnedInstance->GetEnemyBase()->OnDeath.AddDynamic(this, &AEnemyEncounterManager::OnDeathCallback);

	return true;
}

bool AEnemyEncounterManager::SpawnEnemyBase(TSubclassOf<AActor> Reference)
{
	FActorSpawnParameters SpawnParams = FActorSpawnParameters();
	SpawnParams.bNoFail = true;

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

	if (SpawnedInstance->GetController() != nullptr) Cast<AEnemyController>(SpawnedInstance->GetController())->OverrideDefaultPatrolPoints(GenerateRandomPatrolPoints(2));
	else GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("No controller registered for instanced AAIEnemyBase subclass @EnemyEncounterManager"));
	
	SpawnedInstance->GetEnemyBase()->OnDeath.AddDynamic(this, &AEnemyEncounterManager::OnDeathCallback);

	return true;
}

void AEnemyEncounterManager::SpawnEnemies()
{
	if (!CanInitiateEncounter) return;
	if (EncounterHasStarted) return;

	EncounterHasStarted = true;


	for (int i = 0; i <= NumberOfEnemiesToSpawn; i++)
	{

		if (UKismetMathLibrary::RandomBool())
		{
			if (Enemy1_IsSlimeBase)
			{
				if (!SpawnSlimeBase(Enemy1)) break;
			}
			else
			{
				if (!SpawnEnemyBase(Enemy1)) break;
			}
		}

		else
		{
			if (Enemy2_IsSlimeBase)
			{
				if (!SpawnSlimeBase(Enemy2)) break;
			}
			else
			{
				if (!SpawnEnemyBase(Enemy2)) break;
			}
		}
	}
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