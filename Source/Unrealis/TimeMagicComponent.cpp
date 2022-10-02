// a


#include "TimeMagicComponent.h"
#include "Kismet/GameplayStatics.h"
#include "AIEnemyBase.h"
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

		Cast<UCharacterMovementComponent>(Casted->GetMovementComponent())->MaxWalkSpeed = 0.1f;

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

	for (auto e : EnemiesToFreeze)
	{	
		AAIEnemyBase* Casted = Cast<AAIEnemyBase>(e);

		Casted->UnfreezeAnimations();
		Cast<UCharacterMovementComponent>(Casted->GetMovementComponent())->MaxWalkSpeed = 300.f;  // Fixed :smile:
	}

}
