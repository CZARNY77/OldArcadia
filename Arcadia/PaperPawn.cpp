// Fill out your copyright notice in the Description page of Project Settings.


#include "PaperPawn.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "PaperFlipbookComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

APaperPawn::APaperPawn()
{
	PrimaryActorTick.bCanEverTick = true;
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	GetCapsuleComponent()->SetCapsuleSize(37.5f, 37.5f);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("ArmCamera"));
	SpringArm->TargetArmLength = 0.f;
	SpringArm->SocketOffset = FVector(0.f, 0.f, 60.f);
	SpringArm->bEnableCameraLag = true;
	SpringArm->CameraLagSpeed = 40.f;
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->bUsePawnControlRotation = false;
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);

	GetCharacterMovement()->GravityScale = 2.0f;
	GetCharacterMovement()->AirControl = 0.80f;
	GetCharacterMovement()->JumpZVelocity = 1000.f;
	GetCharacterMovement()->GroundFriction = 3.0f;
	GetCharacterMovement()->MaxWalkSpeed = 600.0f;
	GetCharacterMovement()->MaxFlySpeed = 600.0f;

	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->SetPlaneConstraintNormal(FVector(0.0f, -1.0f, 0.0f));

	GetCharacterMovement()->bUseFlatBaseForFloorChecks = true;

	GetSprite()->SetIsReplicated(true);
	bReplicates = true;
}

void APaperPawn::MoveRight(float Val)
{
	AddMovementInput(FVector(0.0f, 1.0f, 0.0f), Val);
}

void APaperPawn::UpdateCharacter()
{
	UpdateAnimation();

	const FVector PlayerVelocity = GetVelocity();
	float TravelDirection = PlayerVelocity.Y;

	if (Controller != nullptr) {
		if (TravelDirection < 0.0f)	GetSprite()->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
		else if (TravelDirection > 0.0f)	GetSprite()->SetRelativeRotation(FRotator(0.0f, 90.0f, 0.0f));
	}
}

void APaperPawn::UpdateAnimation()
{
	const FVector PlayerVelocity = GetVelocity();
	const float PlayerSpeedSqr = PlayerVelocity.SizeSquared();
	if (PlayerVelocity.Z == 0) {
		UPaperFlipbook* DesiredAnimation = (PlayerSpeedSqr > 0.0f) ? RunningAnimation : StandingAnimation;
		if (GetSprite()->GetFlipbook() != DesiredAnimation) {
			GetSprite()->SetFlipbook(DesiredAnimation);
		}
	}
	
	else {
		UPaperFlipbook* DesiredAnimation = JumpingAnimation;
		if (GetSprite()->GetFlipbook() != DesiredAnimation) {
			GetSprite()->SetFlipbook(DesiredAnimation);
		}
	}
}

void APaperPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateCharacter();
}

void APaperPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Right", this, &APaperPawn::MoveRight);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
}
