// a

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundBase.h"
#include "MusicHandlingComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNREALIS_API UMusicHandlingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMusicHandlingComponent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AudioManager)
		TArray<TObjectPtr<USoundBase>> AmbiancePlaylist;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AudioManager)
		TArray<TObjectPtr<USoundBase>> CombatPlaylist;

	UPROPERTY(BlueprintReadWrite)
		TObjectPtr<class UAudioComponent> MusicPlayer;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION()
		void FadeMusicIn();

	UFUNCTION()
		void SwitchTracks();

	UPROPERTY()
		FTimerHandle FadeHandle;


	UPROPERTY()
		int AmbiancePlaylistIndex = 0;

	UPROPERTY()
		int CombatPlaylistIndex = 0;

	UPROPERTY()
		bool CanInitiate = true;

	UPROPERTY()
		bool IsPlayingAmbient = true;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
		FORCEINLINE void SwitchToCombatMusic();

	UFUNCTION(BlueprintCallable)
		FORCEINLINE void SwitchToAmbientMusic();

		
};
