// a

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Fireball.h"
#include "FireballComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNREALIS_API UFireballComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UFireballComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintNativeEvent) //quirk of BNE, it will call the function in c++ then fire the event, not implemented squiggly is a false error
		void CooldownCallback();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite) //unused and unimplemented, if i need it i can, but since i dont have to i wont :p
		TArray<AActor*> SpawnedInstances;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		bool IsInCooldown = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		float CooldownTime = 10.f;



	FTimerHandle CooldownHandle;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
		bool Fire(float MovementSpeed, float DesiredTranslations, float Damage, UStaticMesh* GFXMesh, UStaticMesh* HitboxMesh, FVector Location, FVector ForwardVector, FRotator Rotation, AActor* Owner);

	UFUNCTION(BlueprintCallable)
		void SetCooldownTime(float TimeToSetTo);

	UFUNCTION(BlueprintCallable)
		FORCEINLINE float GetCooldownTime() const { return CooldownTime; }

};
