// Fill out your copyright notice in the Description page of Project Settings.


#include "Gracz2.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Corner.h"
#include "Components/CapsuleComponent.h"

// Sets default values
AGracz2::AGracz2()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("ArmCamera"));
	SpringArm->TargetArmLength = 600.f;
	SpringArm->SetUsingAbsoluteRotation(true);
	SpringArm->bDoCollisionTest = false;
	SpringArm->SocketOffset = FVector(0.f, 0.f, 60.f);
	SpringArm->SetRelativeRotation(FRotator(0.f, 0.f, 0.f));
	SpringArm->bEnableCameraLag = true;
	SpringArm->CameraLagSpeed = 40.f;
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->bUsePawnControlRotation = false;
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);

	GetCharacterMovement()->bOrientRotationToMovement = true; // Face in the direction we are moving..
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->GravityScale = 2.f;
	GetCharacterMovement()->AirControl = 0.80f;
	GetCharacterMovement()->JumpZVelocity = 1000.f;
	GetCharacterMovement()->GroundFriction = 3.f;
	GetCharacterMovement()->MaxWalkSpeed = 600.f;
	GetCharacterMovement()->MaxFlySpeed = 300.f;

	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AGracz2::OnOverlapBegin);

	X = 0.f;
	Y = 1.f;
}

// Called when the game starts or when spawned
void AGracz2::BeginPlay()
{
	Super::BeginPlay();
	
	GetCapsuleComponent()->OnComponentEndOverlap.AddDynamic(this, &AGracz2::OnOverlapEnd);
}

// Called every frame
void AGracz2::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGracz2::MoveRight(float Val)
{
	AddMovementInput(FVector(X, Y, 0.0f), Val);
}

void AGracz2::Action()
{
	if (Corner) {
		//Corner --
		if ((!Corner->AxisX) && (!Corner->AxisY) && (Y==1)) {
			FRotator CurrentR = (SpringArm->GetComponentRotation() + FRotator(0.f, 90.f, 0.f));
			SpringArm->SetWorldRotation(CurrentR);
			X = -1.f;
			Y = 0.f;
		}
		else if ((!Corner->AxisX) && (!Corner->AxisY) && (X == -1)) {
			FRotator CurrentR = (SpringArm->GetComponentRotation() + FRotator(0.f, -90.f, 0.f));
			SpringArm->SetWorldRotation(CurrentR);
			X = 0.f;
			Y = 1.f;
		}

		// Corner -+
		if ((Corner->AxisX) && (!Corner->AxisY) && (Y == 1)) {
			FRotator CurrentR = (SpringArm->GetComponentRotation() + FRotator(0.f, -90.f, 0.f));
			SpringArm->SetWorldRotation(CurrentR);
			X = 1.f;
			Y = 0.f;
		}
		else if ((Corner->AxisX) && (!Corner->AxisY) && (X == 1)) {
			FRotator CurrentR = (SpringArm->GetComponentRotation() + FRotator(0.f, 90.f, 0.f));
			SpringArm->SetWorldRotation(CurrentR);
			X = 0.f;
			Y = 1.f;
		}

		// Corner ++
		if ((Corner->AxisX) && (Corner->AxisY) && (Y == -1)) {
			FRotator CurrentR = (SpringArm->GetComponentRotation() + FRotator(0.f, 90.f, 0.f));
			SpringArm->SetWorldRotation(CurrentR);
			X = 1.f;
			Y = 0.f;
		}
		else if ((Corner->AxisX) && (Corner->AxisY) && (X == 1)) {
			FRotator CurrentR = (SpringArm->GetComponentRotation() + FRotator(0.f, -90.f, 0.f));
			SpringArm->SetWorldRotation(CurrentR);
			X = 0.f;
			Y = -1.f;
		}

		// Corner -+
		if ((!Corner->AxisX) && (Corner->AxisY) && (Y == -1)) {
			FRotator CurrentR = (SpringArm->GetComponentRotation() + FRotator(0.f, -90.f, 0.f));
			SpringArm->SetWorldRotation(CurrentR);
			X = -1.f;
			Y = 0.f;
		}
		else if ((!Corner->AxisX) && (Corner->AxisY) && (X == -1)) {
			FRotator CurrentR = (SpringArm->GetComponentRotation() + FRotator(0.f, 90.f, 0.f));
			SpringArm->SetWorldRotation(CurrentR);
			X = 0.f;
			Y = -1.f;
		}
	}
}

// Called to bind functionality to input
void AGracz2::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveRight", this, &AGracz2::MoveRight);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAction("Action", IE_Pressed, this, &AGracz2::Action);
}

void AGracz2::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Corner = Cast<ACorner>(OtherActor);
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Black, TEXT("Gracz Wszed³"));
	
	
}

void AGracz2::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Corner = NULL;
}