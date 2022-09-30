// a


#include "DebuggingPawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "FireballComponent.h"

// Sets default values
ADebuggingPawn::ADebuggingPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Possess player as soon as game starts
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	//Initialize components for our player

	SpringArm = CreateDefaultSubobject<USpringArmComponent>("CameraArm");
	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	CapsuleCollider = CreateDefaultSubobject<UCapsuleComponent>("CapsuleCollider");
	CapsuleTrigger = CreateDefaultSubobject<UCapsuleComponent>("CapsuleTrigger");

	//Setup our camera to follow the player
	SpringArm->SetupAttachment(CapsuleCollider);
	CapsuleTrigger->SetupAttachment(CapsuleCollider);
	Camera->SetupAttachment(SpringArm);

	CapsuleCollider->SetSimulatePhysics(true);

	//Configure the USpringArmComponent
	SpringArm->SetRelativeLocationAndRotation(FVector(0.f, 0.f, 0.f), FRotator(-20.f, 0.f, 0.f));

	//self explanatory
	MovementSpeed = 20;
	RotationSensitivity = 2;


}

// Called when the game starts or when spawned
void ADebuggingPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADebuggingPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ADebuggingPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("ForwardsMovement", this, &ADebuggingPawn::MoveForwards);
	PlayerInputComponent->BindAxis("SideMovement", this, &ADebuggingPawn::MoveSideways);
	PlayerInputComponent->BindAxis("XMouseMovement", this, &ADebuggingPawn::Rotate);
	PlayerInputComponent->BindAction("Attack1", IE_Pressed, this, &ADebuggingPawn::AttackOne);
	PlayerInputComponent->BindAction("SwitchElement", IE_Pressed, this, &ADebuggingPawn::SwitchElement);

}

void ADebuggingPawn::AttackOne_Implementation()
{

}

void ADebuggingPawn::SwitchElement_Implementation()
{

}

void ADebuggingPawn::MoveForwards(float AxisValue)
{
	if (AxisValue == 0) return;

	FVector Location = GetActorLocation();

	Location += GetActorForwardVector() * MovementSpeed * AxisValue;

	SetActorRelativeLocation(Location);
}

void ADebuggingPawn::MoveSideways(float AxisValue)
{
	if (AxisValue == 0) return;

	FVector Location = GetActorLocation();

	Location += GetActorRightVector() * MovementSpeed * AxisValue;

	SetActorRelativeLocation(Location);
}

void ADebuggingPawn::Rotate(float AxisValue)
{
	if (AxisValue == 0) return;

	FRotator Rotation = GetActorRotation();

	Rotation.Add(0.f, RotationSensitivity * AxisValue, 0.f);

	SetActorRotation(Rotation);
}

