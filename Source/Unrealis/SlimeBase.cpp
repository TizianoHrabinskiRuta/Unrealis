// a


#include "SlimeBase.h"
#include "EnemyBaseComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "EnemyController.h"
#include "Perception/PawnSensingComponent.h"

// Sets default values
ASlimeBase::ASlimeBase()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	Hitbox = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Hitbox"));
	CharacterMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh"));
	PawnSensor = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensor"));
	HealthComponent = CreateDefaultSubobject<UEnemyBaseComponent>(TEXT("HealthComponent"));

	RootComponent = Hitbox;

	CharacterMesh->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ASlimeBase::BeginPlay()
{
	Super::BeginPlay();

	AEnemyController* SelfController = Cast<AEnemyController>(GetController());

	if (SelfController)
	{
		SelfController->OnAttack1Call.AddDynamic(this, &ASlimeBase::ExecuteAttack1);
	}

	if (HealthComponent)
		this->HealthComponent->OnDeath.AddDynamic(this, &ASlimeBase::OnDeathCallback); else GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Didnt instance EBC correctly @AIEnemyBase"));
	this->PawnSensor->OnSeePawn.AddDynamic(this, &ASlimeBase::OnPlayerCaught);

	if (Hitbox) Hitbox->OnComponentHit.AddDynamic(this, &ASlimeBase::CheckForGroundHit);
	

}


void ASlimeBase::OnPlayerCaught(APawn* CaughtPawn)
{

	AEnemyController* SelfController = Cast<AEnemyController>(GetController());

	if (SelfController)
	{
		SelfController->SetPlayerCaught(CaughtPawn);
	}
}



#pragma region BlueprintNativeEvents
void ASlimeBase::OnDeathCallback_Implementation()
{
	Destroy();
}

void ASlimeBase::ExecuteAttack1_Implementation()
{

}

void ASlimeBase::FreezeAnimations_Implementation()
{

}

void ASlimeBase::UnfreezeAnimations_Implementation()
{

}

#pragma endregion




// Called every frame
void ASlimeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASlimeBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


void ASlimeBase::CheckForGroundHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{	
	if (OtherActor->ActorHasTag("FloorTag")) { bIsGrounded = true; OnGround.Broadcast(); GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Recieved hit")); bIsGrounded = false; return; }
	
	return;
}