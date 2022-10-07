// a


#include "TimeMagicComponent.h"
#include "Kismet/GameplayStatics.h"
#include "AIEnemyBase.h"
#include "BrainComponent.h"
#include "AIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PawnMovementComponent.h"



// Sets default values for this component's properties
UTimeMagicComponent::UTimeMagicComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTimeMagicComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTimeMagicComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


void UTimeMagicComponent::FreezeEnemies()
{

	if (InCooldown) return;

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAIEnemyBase::StaticClass(), EnemiesToFreeze);

	for (auto e : EnemiesToFreeze)
	{
		AAIEnemyBase* Casted = Cast<AAIEnemyBase>(e);

		Casted->FreezeAnimations();

		UCharacterMovementComponent* Ref = Cast<UCharacterMovementComponent>(Casted->GetMovementComponent());

		Ref->MaxWalkSpeed = 0.1f;

		FRotator i = FRotator::ZeroRotator;

		Ref->RotationRate = i; // sorta works, is just visual so i wont fix it until later @TODO

		
		Cast<AAIController>(Casted->GetController())->BrainComponent->PauseLogic(TEXT("Freeze"));
	}

	GetWorld()->GetTimerManager().SetTimer(UnfreezeDelegate, this, &UTimeMagicComponent::UnfreezeCallback, FreezeTime, false);
	GetWorld()->GetTimerManager().SetTimer(CooldownDelegate, this, &UTimeMagicComponent::CooldownCallback, CooldownTime, false);

	InCooldown = true;
}

void UTimeMagicComponent::CooldownCallback()
{
	InCooldown = false;
}

void UTimeMagicComponent::UnfreezeCallback()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Should Unfreeze"));

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAIEnemyBase::StaticClass(), EnemiesToFreeze);

	for (auto e : EnemiesToFreeze) // for each enemy that currently exists
	{	
		AAIEnemyBase* Casted = Cast<AAIEnemyBase>(e);

		Casted->UnfreezeAnimations(); // call a custom function that sets the animplayrate to 1

		UCharacterMovementComponent* Ref = Cast<UCharacterMovementComponent>(Casted->GetMovementComponent());

		Ref->MaxWalkSpeed = 300.f;  // Make them be able to move again
		FRotator i = FRotator::ZeroRotator;

		i.Add(30.f, 0.f, 0.f); // Set the following rotation speed back to default

		Ref->RotationRate = i;
		Cast<AAIController>(Casted->GetController())->BrainComponent->ResumeLogic(TEXT("Freeze")); // Resume execution of BT
	}

}
