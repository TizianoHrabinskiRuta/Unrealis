// a


#include "LightningAttack.h"
#include "EnemyBaseComponent.h"
#include "AIEnemyBase.h"

// Sets default values
ALightningAttack::ALightningAttack()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	GFX = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GFX"));

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

void ALightningAttack::CheckForColission(FVector SpawnLocation, FVector ForwardsVector, FRotator SpawnRotation)
{
	FHitResult RaycastResult;

	FCollisionQueryParams QueryParams;

	QueryParams.AddIgnoredActor(this->GetOwner());

	FVector BeamEnd = SpawnLocation + ForwardsVector * Length;

	DrawDebugLine(GetWorld(), SpawnLocation, BeamEnd, FColor::Red, false, 5.f);

	if (GetWorld()->LineTraceSingleByChannel(RaycastResult, SpawnLocation, BeamEnd, ECC_Pawn, QueryParams)) // find ECC for physics objkects, or for things that arent necessarily visible, since the hitbox is hidden in play
	{
		AAIEnemyBase* HitEnemy = Cast<AAIEnemyBase>(RaycastResult.GetActor());

		if (HitEnemy)
			HitEnemy->GetEnemyBase()->TakeDamage(this->Damage);

		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, TEXT("Hit something"));
	}
	else GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, TEXT("Either missed or didnt detect (sadge)"));
}

