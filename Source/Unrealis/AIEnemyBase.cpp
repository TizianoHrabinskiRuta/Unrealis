// Fill out your copyright notice in the Description page of Project Settings.


#include "AIEnemyBase.h"
#include "EnemyBaseComponent.h"
#include "EnemyController.h"
#include "Perception/PawnSensingComponent.h"

// Sets default values
AAIEnemyBase::AAIEnemyBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	HealthComponent = CreateDefaultSubobject<UEnemyBaseComponent>(TEXT("EnemyBase"));
	PawnSensor = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensor"));
	
	AIControllerClass = FindObject<UClass>(ANY_PACKAGE, TEXT("AEnemyController"));

}

// Called when the game starts or when spawned
void AAIEnemyBase::BeginPlay()
{
	Super::BeginPlay();
	
	AEnemyController* SelfController = Cast<AEnemyController>(GetController());

	if (SelfController)
	{
		SelfController->OnAttack1Call.AddDynamic(this, &AAIEnemyBase::ExecuteAttack1);
	}
	

	if (HealthComponent)
		this->HealthComponent->OnDeath.AddDynamic(this, &AAIEnemyBase::OnDeathCallback); else GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Didnt instance EBC correctly @AIEnemyBase"));
	this->PawnSensor->OnSeePawn.AddDynamic(this, &AAIEnemyBase::OnPlayerCaught);
}


void AAIEnemyBase::OnPlayerCaught(APawn* CaughtPawn)
{

	AEnemyController* SelfController = Cast<AEnemyController>(GetController());

	if (SelfController)
	{
		SelfController->SetPlayerCaught(CaughtPawn);
	}
}

#pragma region BlueprintNativeEvents
void AAIEnemyBase::OnDeathCallback_Implementation()
{
	Destroy();
}

void AAIEnemyBase::ExecuteAttack1_Implementation()
{
	
}

void AAIEnemyBase::FreezeAnimations_Implementation()
{

}

void AAIEnemyBase::UnfreezeAnimations_Implementation()
{

}

#pragma endregion

// Called every frame
void AAIEnemyBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AAIEnemyBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
