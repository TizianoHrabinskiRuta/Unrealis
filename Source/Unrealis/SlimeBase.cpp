// a


#include "SlimeBase.h"
#include "EnemyBaseComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
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

#pragma region Movement Logic

void ASlimeBase::SwitchPatrolPoint()
{
	if (SelectedPatrolPointIndex + 1 > (PatrolPoints.Num() - 1)) SelectedPatrolPointIndex = 0;
	else SelectedPatrolPointIndex++;
}

bool ASlimeBase::HasReachedDestination()
{
	if (FVector::Distance(GetActorLocation(), GetCurrentTarget()->GetActorLocation()) <= DistanceThreshold && !IsPlayerTheCurrentTarget()) 
	{ 
		SwitchPatrolPoint();
	    return true; 
	}

	return false;
}

void ASlimeBase::OnPlayerCaught(APawn* CaughtPawn)
{
	CaughtPlayer = CaughtPawn;
}

AActor* ASlimeBase::GetCurrentTarget()
{
	if (!CaughtPlayer) return GetCurrentPatrolPoint(); 
	else return CaughtPlayer;
}

bool ASlimeBase::IsPlayerTheCurrentTarget()
{
	if(CaughtPlayer)
	return true;

	return false;
}

void ASlimeBase::FireJumpRequest()
{
	SetActorRotation(UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), GetCurrentTarget()->GetActorLocation()));

	FVector VectorialForwardsForceToApply = FVector();
	VectorialForwardsForceToApply += GetActorForwardVector() * ForwardsForceToApply;

	FVector VectorialUpwardsForceToApply = FVector(0.f, 0.f, UpwardsForceToApply);

	UPrimitiveComponent* OwnerPrimitive = Cast<UPrimitiveComponent>(GetRootComponent());

	OwnerPrimitive->AddImpulse(VectorialUpwardsForceToApply);
	OwnerPrimitive->AddImpulse(VectorialForwardsForceToApply);

}

#pragma endregion

#pragma region BlueprintNativeEvents
void ASlimeBase::OnDeathCallback_Implementation()
{
	Destroy();
}
void ASlimeBase::OnGroundEvent2_Implementation()
{

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

void ASlimeBase::RequestJump_Implementation()
{

}

#pragma endregion

// Called every frame
void ASlimeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	HasReachedDestination();
}

// Called to bind functionality to input
void ASlimeBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ASlimeBase::CheckForGroundHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{	
	if (OtherActor->ActorHasTag("FloorTag")) { bIsGrounded = true; OnGround.Broadcast(); OnGroundEvent2();  bIsGrounded = false; }	
	return;
}

void ASlimeBase::OverrideDefaultPatrolPoints(TArray<AActor*> InPatrolPoints)
{
	PatrolPoints.Empty();
	SelectedPatrolPointIndex = 0;

	for (auto h : InPatrolPoints)
	{
		PatrolPoints.Add(h);
	}
}