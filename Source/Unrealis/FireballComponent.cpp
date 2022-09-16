// a


#include "FireballComponent.h"
#include "Fireball.h"

// Sets default values for this component's properties
UFireballComponent::UFireballComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UFireballComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UFireballComponent::CooldownCallback_Implementation()
{
	this->IsInCooldown = false;
}


// Called every frame
void UFireballComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool UFireballComponent::Fire(float MovementSpeed, float DesiredTranslations, float Damage, UStaticMesh* GFXMesh, UStaticMesh* HitboxMesh, FVector Location, FVector ForwardVector, FRotator Rotation)
{
	if (IsInCooldown) return false;

	FVector UpdatedLocation = Location;
	UpdatedLocation += ForwardVector * 25.f;

	AFireball* SpawnedInstance = GetWorld()->SpawnActor<AFireball>(UpdatedLocation, Rotation);

	if (SpawnedInstance)
	{
		GetWorld()->GetTimerManager().SetTimer(CooldownHandle, this, &UFireballComponent::CooldownCallback, 1.f, false);
		this->IsInCooldown = true;
		return true;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to spawn fireball"));
		return false;
	}	
}

void UFireballComponent::SetCooldownTime(float TimeToSetTo)
{
	this->CooldownTime = TimeToSetTo;
}

