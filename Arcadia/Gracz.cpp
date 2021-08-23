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
	SpringArm->SocketOffset = FVector(0.f, 0.f, 0.f);
	SpringArm->bEnableCameraLag = true;
	SpringArm->CameraLagSpeed = 15.f;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(RootComponent);
	Camera->bUsePawnControlRotation = true;
}

void AGracz::BeginPlay()
{
	Super::BeginPlay();
	
}

void AGracz::MoveRight(float Val)
{

}

void AGracz::Jump(float Val)
{
}

void AGracz::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGracz::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Right", this, &AGracz::MoveRight);
	PlayerInputComponent->BindAxis("Jump", this, &AGracz::Jump);
}

