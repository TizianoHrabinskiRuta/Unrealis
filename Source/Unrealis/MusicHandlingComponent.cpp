// a


#include "MusicHandlingComponent.h"
#include "EngineGlobals.h"


// Sets default values for this component's properties
UMusicHandlingComponent::UMusicHandlingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	MusicPlayer = CreateDefaultSubobject<UAudioComponent>(TEXT("MusicPlayer"));

	if (GetOwner())
		MusicPlayer->SetupAttachment(GetOwner()->GetRootComponent());

	// ...
}


// Called when the game starts
void UMusicHandlingComponent::BeginPlay()
{
	Super::BeginPlay();

	if (AmbiancePlaylist.Num() == 0)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("No music in ambiance queue @MusicHandlingComponent"));
		CanInitiate = false;
	}
	
	if (CombatPlaylist.Num() == 0)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("No music in combat queue @MusicHandlingComponent"));
		CanInitiate = false;
	}


	if (CanInitiate)
	{
		MusicPlayer->SetSound(AmbiancePlaylist[AmbiancePlaylistIndex]);
		MusicPlayer->VolumeMultiplier = 1.f;
		MusicPlayer->bAllowSpatialization = false;
		MusicPlayer->OnAudioFinished.AddDynamic(this, &UMusicHandlingComponent::SwitchTracks);
		MusicPlayer->Play();
	}

}

void UMusicHandlingComponent::FadeMusicIn()
{

	if (IsPlayingAmbient)
	{
		MusicPlayer->SetSound(AmbiancePlaylist[AmbiancePlaylistIndex]);
		MusicPlayer->FadeIn(1.f, 1.f, 0.f);
	}
	else
	{
		MusicPlayer->SetSound(CombatPlaylist[CombatPlaylistIndex]);
		MusicPlayer->FadeIn(1.f, 1.f, 0.f);
	}
}

void UMusicHandlingComponent::FadeSpecifiedMusicIn()
{
	if (IndexOfSpecifiedMusic == NULL) { GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("There was an error fading in music @MusicHandlingComponent::FadeSpecifiedMusicIn")); return; }

	MusicPlayer->SetSound(CombatPlaylist[IndexOfSpecifiedMusic]);
	MusicPlayer->FadeIn(1.f, 1.f, 0.f);

}

void UMusicHandlingComponent::SwitchTracks()
{
	if (BossMusicOverride) return;

	if (IsPlayingAmbient)
	{
		if (AmbiancePlaylistIndex + 1 > AmbiancePlaylist.Num() - 1) { AmbiancePlaylistIndex = 0; MusicPlayer->SetSound(AmbiancePlaylist[0]); }
		else { AmbiancePlaylistIndex++; MusicPlayer->SetSound(AmbiancePlaylist[AmbiancePlaylistIndex]); }
	}
	else
	{
		if (CombatPlaylistIndex + 1 > CombatPlaylist.Num() - 1) { CombatPlaylistIndex = 0; MusicPlayer->SetSound(CombatPlaylist[0]); }
		else { CombatPlaylistIndex++; MusicPlayer->SetSound(CombatPlaylist[CombatPlaylistIndex]); }
	}
}


// Called every frame
void UMusicHandlingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UMusicHandlingComponent::SwitchToCombatMusic()
{
	MusicPlayer->FadeOut(1.f, 0.f);
	
	GetWorld()->GetTimerManager().SetTimer(FadeHandle, this, &UMusicHandlingComponent::FadeMusicIn, 1.f, false);

	IsPlayingAmbient = false;

}


 void UMusicHandlingComponent::SwitchToAmbientMusic()
 {
	 MusicPlayer->FadeOut(1.f, 0.f);

	 GetWorld()->GetTimerManager().SetTimer(FadeHandle, this, &UMusicHandlingComponent::FadeMusicIn, 1.f, false);

	 IsPlayingAmbient = true;
 }

 void UMusicHandlingComponent::SwitchToCombatMusicAtIndex(int Index, bool IsForBossMusic)
 {
	 if (!CombatPlaylist.IsValidIndex(Index)) { GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("No music pointer exists at this index @MusicHandlingComponent::SwitchToCombatMusicAtIndex")); return; }
	 if (IsForBossMusic) BossMusicOverride = true;

	 IndexOfSpecifiedMusic = Index;

	 MusicPlayer->FadeOut(1.f, 0.f);

	 GetWorld()->GetTimerManager().SetTimer(FadeHandle, this, &UMusicHandlingComponent::FadeSpecifiedMusicIn, 1.f, false);

	 IsPlayingAmbient = false;
 }

 