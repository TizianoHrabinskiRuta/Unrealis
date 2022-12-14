// a


#include "Fireball.h"
#include "EnemyBaseComponent.h"
#include "SlimeBase.h"
#include "AIEnemyBase.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AFireball::AFireball()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	this->Hitbox = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Hitbox"));
	this->GFX = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GFX"));


	RootComponent = Hitbox;

	GFX->SetupAttachment(RootComponent);
	Hitbox->SetVisibility(false, false);
	GFX->SetVisibility(true);
}

// Called when the game starts or when spawned
void AFireball::BeginPlay()
{
	Hitbox->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	GFX->SetCollisionProfileName(TEXT("NoCollision"));

	Super::BeginPlay();
	this->Hitbox->OnComponentBeginOverlap.AddDynamic(this, &AFireball::OnOverlapBegin);
	this->Hitbox->OnComponentHit.AddDynamic(this, &AFireball::OnHit);
	this->Tags.Add(TEXT("Fireball"));	
}

void AFireball::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor->ActorHasTag("EnemyTag"))
	{
		if (Cast<AAIEnemyBase>(OtherActor))
		{
			 Cast<AAIEnemyBase>(OtherActor)->GetEnemyBase()->TakeDamage(this->Damage);
			
		}
		else
		{
			UEnemyBaseComponent* SlimeBase = Cast<ASlimeBase>(OtherActor)->GetEnemyBase();
			if (SlimeBase)
			{
				SlimeBase->TakeDamage(this->Damage);
			}
		}
	}

	if (OtherActor->ActorHasTag("FireballDestructibleWall"))
	{
		OtherActor->Destroy();
	}


	if (!OtherActor->ActorHasTag("PlayerTag"))
	{
		OnDestruction.Broadcast(this, GetActorLocation());
		Destroy();
	}
}



void AFireball::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult)
{	

	if (OtherActor->ActorHasTag("EnemyTag"))
	{
		if (Cast<AAIEnemyBase>(OtherActor))
		{
			UEnemyBaseComponent* Base = Cast<AAIEnemyBase>(OtherActor)->GetEnemyBase();

			Base->TakeDamage(this->Damage);
		}
		else
		{
			UEnemyBaseComponent* SlimeBase = Cast<ASlimeBase>(OtherActor)->GetEnemyBase();
			if (SlimeBase)
			{
				SlimeBase->TakeDamage(this->Damage);
			}
		}
	}

	if (OtherActor->ActorHasTag("FireballDestructibleWall"))
	{
		OtherActor->Destroy();
	}


	if (!OtherActor->ActorHasTag("PlayerTag"))
	{
		OnDestruction.Broadcast(this, GetActorLocation());
		Destroy();
	}

	
}

void AFireball::SetMovementParameters(float SpeedToSetTo, float _DesiredTranslations)
{
	this->MovementSpeed = SpeedToSetTo;
	this->DesiredTranslations = _DesiredTranslations;
}

void AFireball::SetGFXAndHitbox(UStaticMesh* GFXMesh, UStaticMesh* HitboxMesh)
{
	this->GFX->SetStaticMesh(GFXMesh);
	this->Hitbox->SetStaticMesh(HitboxMesh);
}

void AFireball::MasterFunction(float SpeedToSetTo, float _DesiredTranslations, float DamageToSetTo, UStaticMesh* GFXMesh, UStaticMesh* HitboxMesh)
{
	this->MovementSpeed = SpeedToSetTo;
	this->DesiredTranslations = _DesiredTranslations;

	this->Damage = DamageToSetTo;

	this->GFX->SetStaticMesh(GFXMesh);
	this->Hitbox->SetStaticMesh(HitboxMesh);
}

void AFireball::SetDamage(float DamageToSetTo)
{
	this->Damage = DamageToSetTo;
}

void AFireball::Move()
{
	if (this->TranscurredTranslations <= this->DesiredTranslations)
	{
		FVector Location = this->GetActorLocation();

		Location += GetActorForwardVector() * this->MovementSpeed;

		this->SetActorLocation(Location);
		TranscurredTranslations++;
	}
	else
	{
		OnDestruction.Broadcast(this, GetActorLocation());

	}
}

void AFireball::StartMoving()
{
	this->ShouldMove= true;
}

// Called every frame
void AFireball::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(ShouldMove)
	Move();

	if (SetPlayerReference)
	{
		GFX->SetWorldRotation(UKismetMathLibrary::FindLookAtRotation(GFX->GetComponentLocation(), SetPlayerReference->GetActorLocation()));
	}

}

