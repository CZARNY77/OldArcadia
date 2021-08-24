#include "Gracz.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

AGracz::AGracz()
{
 	PrimaryActorTick.bCanEverTick = true;
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	MainMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MainMesh_1"));
	RootComponent = MainMesh;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("ArmCamera"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = 0.f;
	SpringArm->SocketOffset = FVector(0.f, 0.f, 60.f);
	SpringArm->bEnableCameraLag = true;
	SpringArm->CameraLagSpeed = 40.f;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
	Camera->bUsePawnControlRotation = true;

	MaxSpeed = 300.f;
	pJump = false;
}

void AGracz::BeginPlay()
{
	Super::BeginPlay();
	
}

void AGracz::MoveRight(float Val)
{
	if (Val > 0.2f || Val < -0.2f) {
		float NewSpeed = Speed + (GetWorld()->GetDeltaSeconds() * (Val * 100.f));
		Speed = FMath::Clamp(NewSpeed, -MaxSpeed, MaxSpeed);
	}
	else if(Speed != 0.f) {
		bool bSpeed = Speed > 0.f;
		float Slow = bSpeed ? -5 : 5;
		float NewSpeed = Speed + (GetWorld()->GetDeltaSeconds() * (Slow * 100.f));
		Speed = bSpeed ? FMath::Clamp(NewSpeed, 0.f, MaxSpeed) : FMath::Clamp(NewSpeed, -MaxSpeed, 0.f);
	}
}

void AGracz::Jump()
{
	if (pJump) {
		Up = 0.f;
		pJump = false;
	}
	else {
		Up = 400.f;
		pJump = true;
	}
}

void AGracz::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	const FVector LocalMove = FVector(0.f, Speed * DeltaTime, Up * DeltaTime);
	AddActorLocalOffset(LocalMove, true);
}

void AGracz::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Right", this, &AGracz::MoveRight);
	PlayerInputComponent->BindAction("Jump", IE_Pressed ,this, &AGracz::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AGracz::Jump);
}

