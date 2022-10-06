// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyBaseComponent.h"

// Sets default values for this component's properties
UEnemyBaseComponent::UEnemyBaseComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	Health = MaxHealth;
	// ...
}


// Called when the game starts
void UEnemyBaseComponent::BeginPlay()
{
	Super::BeginPlay();


	// ...
	
}

void UEnemyBaseComponent::CheckForDeath()
{
	if (Health <= 0)
	{
		OnDeath.Broadcast();
		HasDied();
	}
}

void UEnemyBaseComponent::HasDied_Implementation()
{

}

void UEnemyBaseComponent::TakeDamage(float Damage)
{
	this->Health -= Damage;
	OnDamaged.Broadcast(Damage);
}
// Called every frame
void UEnemyBaseComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	CheckForDeath();

	// ...
}

