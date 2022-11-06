// a


#include "LootDropComponent.h"

// Sets default values for this component's properties
ULootDropComponent::ULootDropComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void ULootDropComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

TArray<FString> CalculateDrops(TMap<FString, float> InMap)
{
	TArray<FString> ReturningItems;
	FRandomStream Generator = FRandomStream();

	for (auto h : InMap) 
	{
		if (h.Value >= Generator.FRandRange(0.02, 100)) ReturningItems.Add(h.Key);
	}
	
	return ReturningItems;
}


// Called every frame
void ULootDropComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

