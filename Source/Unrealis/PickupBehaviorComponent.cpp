// a


#include "PickupBehaviorComponent.h"
#include "Components/SphereComponent.h"

// Sets default values for this component's properties
UPickupBehaviorComponent::UPickupBehaviorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	SpherePickupRadius = CreateDefaultSubobject<USphereComponent>(TEXT("SpherePickupRadius"));
	if (GetOwner())
		SpherePickupRadius->SetupAttachment(GetOwner()->GetRootComponent());

	SpherePickupRadius->SetVisibility(true);
	
	SpherePickupRadius->InitSphereRadius(400.f);
}


// Called when the game starts
void UPickupBehaviorComponent::BeginPlay()
{
	Super::BeginPlay();

	if (GetOwner())
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, GetOwner()->GetName());

	
	
	SpherePickupRadius->OnComponentBeginOverlap.AddDynamic(this, &UPickupBehaviorComponent::OnOverlapBegin);
	// ...
	
}

void UPickupBehaviorComponent::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->ActorHasTag("PlayerTag"))
	{
		OnPlayerPickup.Broadcast(OtherActor);
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("no player"));
	}
}

// Called every frame
void UPickupBehaviorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

