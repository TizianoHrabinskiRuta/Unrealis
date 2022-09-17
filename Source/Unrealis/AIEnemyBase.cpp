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

	EnemyBaseComponent = CreateDefaultSubobject<UEnemyBaseComponent>(TEXT("EnemyBase"));
	PawnSensor = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensor"));

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

	this->EnemyBaseComponent->OnDeath.AddDynamic(this, &AAIEnemyBase::OnDeathCallback);
	this->PawnSensor->OnSeePawn.AddDynamic(this, &AAIEnemyBase::OnPlayerCaught);
}


void AAIEnemyBase::OnPlayerCaught(APawn* CaughtPawn)
{
	//REMEMBER TO ADD REFERENCES TO THE KEYS IN BB @TODO

	AEnemyController* SelfController = Cast<AEnemyController>(GetController());

	if (SelfController)
	{
		SelfController->SetPlayerCaught(CaughtPawn);
	}
}

void AAIEnemyBase::OnDeathCallback_Implementation()
{
	Destroy();
}

void AAIEnemyBase::ExecuteAttack1_Implementation()
{
	
}


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

