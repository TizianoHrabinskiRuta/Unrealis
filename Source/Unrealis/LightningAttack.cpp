// a


#include "LightningAttack.h"
#include "EnemyBaseComponent.h"
#include "AIEnemyBase.h"
#include "SlimeBase.h"
#include "DebuggingPawn.h"

// Sets default values
ALightningAttack::ALightningAttack()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	GFX = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GFX"));

}

void ShowMessage(FString Message)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, Message);
}

// Called when the game starts or when spawned
void ALightningAttack::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(GFXOpacityHandle, this, &ALightningAttack::StartOpacityChanges, 0.3f, false); // Edit the float here to make the graphical element stay visible for longer @INFO
}

// Called every frame
void ALightningAttack::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void ALightningAttack::StartOpacityChanges()
{
	GFX->SetVisibility(false);
}

void ALightningAttack::SetParams(UStaticMesh* GFXMesh, FRotator Rotation) // Sets the Graphical texture and adjusts the rotation so it matches the origin
{
	GFX->SetStaticMesh(GFXMesh);

	FRotator CalcRotation = Rotation;

	CalcRotation.Pitch += 90.f;

	GFX->SetWorldRotation(CalcRotation);

	GFX->SetVisibility(true);
}

void ALightningAttack::SetDamage(float FDamage)
{
	this->Damage = FDamage;
}

void ALightningAttack::CheckForColission(FVector SpawnLocation, FVector ForwardsVector, FRotator SpawnRotation, AActor* OwnerRef) // Broken, most likely is colliding with caster for some reason. Maybe try a multihit linetrace, or set spawn point further into the map
{
	TArray<FHitResult> HitResultReturn;
	FHitResult RaycastResult;

	FCollisionQueryParams QueryParams;

	QueryParams.AddIgnoredActor(OwnerRef);

	FVector CalcSpawnLocation = SpawnLocation;
	SpawnLocation += ForwardsVector * 5000.f;

	FVector BeamEnd = CalcSpawnLocation + ForwardsVector * Length;

	Passer.Broadcast(BeamEnd, SpawnLocation);

	DrawDebugLine(GetWorld(), CalcSpawnLocation, BeamEnd, FColor::Red, false, 5.f);

	if (GetWorld()->LineTraceMultiByChannel(HitResultReturn, CalcSpawnLocation, BeamEnd, ECC_Visibility, QueryParams))
	{
		for (auto h : HitResultReturn)
		{
			if (Cast<AAIEnemyBase>(h.GetActor())) Cast<AAIEnemyBase>(h.GetActor())->GetEnemyBase()->TakeDamage(this->Damage);

			if (Cast<ASlimeBase>(h.GetActor())) { Cast<ASlimeBase>(h.GetActor())->GetEnemyBase()->TakeDamage(this->Damage); return; }

			if (Cast<ADebuggingPawn>(h.GetActor())) ShowMessage(TEXT("Hit self again"));
		}
		
	}
	
}

