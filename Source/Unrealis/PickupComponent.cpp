// a


#include "PickupComponent.h"
#include "Components/CapsuleComponent.h"

// Sets default values for this component's properties
UPickupComponent::UPickupComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	CapsulePickupRadius = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsulePickupRadius"));

	// ...
}


// Called when the game starts
void UPickupComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UPickupComponent::AttachToParent(USceneComponent* Parent)
{

	CapsulePickupRadius->SetupAttachment(Parent);
}

// Called every frame
void UPickupComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

