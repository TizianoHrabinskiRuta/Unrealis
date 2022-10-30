// a


#include "VRCharacterComponent.h"
#include "Components/InputComponent.h"

// Sets default values for this component's properties
UVRCharacterComponent::UVRCharacterComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	this->Health = MaxHealth;
	PlayerInputComponent = CreateDefaultSubobject<UInputComponent>(TEXT("InputComp"));
	// ...
}


// Called when the game starts
void UVRCharacterComponent::BeginPlay()
{
	Super::BeginPlay();

	PlayerInputComponent->BindAction("Attack1", IE_Pressed, this, &UVRCharacterComponent::Attack1);
	PlayerInputComponent->BindAction("SwitchElement", IE_Pressed, this, &UVRCharacterComponent::CallElementChangeEvent);
}

void UVRCharacterComponent::HealPlayer(float InHealth)
{
	this->Health += InHealth;
	OnHeal.Broadcast(InHealth);
}

void UVRCharacterComponent::Attack1()
{
	Attack1Event.Broadcast();
}

// Called every frame
void UVRCharacterComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UVRCharacterComponent::CallElementChangeEvent()
{
	OnElementChange.Broadcast();
}

void UVRCharacterComponent::TakeDamage(float Damage)
{
	this->Health -= Damage * DefenseMultiplier;
	OnDamaged.Broadcast(Damage);

	if (Health <= 0)
		OnDeath.Broadcast();
}

