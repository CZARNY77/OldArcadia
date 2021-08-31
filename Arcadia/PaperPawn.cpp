// Fill out your copyright notice in the Description page of Project Settings.


#include "PaperPawn.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "PaperFlipbookComponent.h"

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
}

void APaperPawn::MoveRight(float Val)
{
	AddMovementInput(FVector(1.0f, 0.0f, 0.0f), Val);
}

void APaperPawn::UpdateCharacter()
{
}

void APaperPawn::UpdateAnimation()
{
}

void APaperPawn::StartedJump(const ETouchIndex::Type FingerIndex, const FVector Location)
{
}

void APaperPawn::StopedJump(const ETouchIndex::Type FingerIndex, const FVector Location)
{
}

void APaperPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APaperPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveRight", this, &APaperPawn::MoveRight);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
}
