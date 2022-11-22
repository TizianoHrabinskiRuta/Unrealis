// a


#include "SwordHolderComponent.h"

// Sets default values for this component's properties
USwordHolderComponent::USwordHolderComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	DropRadius = CreateDefaultSubobject<USphereComponent>(TEXT("DropRadius"));

	if (GetOwner())
		DropRadius->SetupAttachment(GetOwner()->GetRootComponent());

	// ...
}


// Called when the game starts
void USwordHolderComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void USwordHolderComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

