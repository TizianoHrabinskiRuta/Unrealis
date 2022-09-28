// a

#include "LightningAttackComponent.h"
#include "LightningAttack.h"



// Sets default values for this component's properties
ULightningAttackComponent::ULightningAttackComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	// ...
}


// Called when the game starts
void ULightningAttackComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void ULightningAttackComponent::CooldownCallback()
{
	IsInCooldown = false;
}


// Called every frame
void ULightningAttackComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void ULightningAttackComponent::FireLightning(UStaticMesh* GFXMesh, FVector SpawnLocation, FVector ForwardsVector, FRotator SpawnRotation)
{
	if (IsInCooldown) return;
	GetWorld()->GetTimerManager().SetTimer(CooldownHandle, this, &ULightningAttackComponent::CooldownCallback, CooldownTime);
	IsInCooldown = true;
	

	ALightningAttack* SpawnedLightning = GetWorld()->SpawnActor<ALightningAttack>(SpawnLocation, SpawnRotation);
	SpawnedLightning->SetParams(GFXMesh, SpawnRotation);
	SpawnedLightning->SetDamage(AttackDamage);
	SpawnedLightning->CheckForColission(SpawnLocation, ForwardsVector, SpawnRotation);
}

void ULightningAttackComponent::SetDamage(float DamageToSetTo)
{
	this->AttackDamage = DamageToSetTo;
}

void ULightningAttackComponent::ChangeCooldownTime(float TimeToSetTo)
{
	this->CooldownTime = TimeToSetTo;
}
