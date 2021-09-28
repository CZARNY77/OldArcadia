// Fill out your copyright notice in the Description page of Project Settings.


#include "FlyingMob.h"
#include "Components/BoxComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Math.h"

// Sets default values
AFlyingMob::AFlyingMob()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DummyRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Dummy"));
	RootComponent = DummyRoot;

	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	Box->SetupAttachment(RootComponent);

	Speed = 0.5f;
}

// Called when the game starts or when spawned
void AFlyingMob::BeginPlay()
{
	Super::BeginPlay();

	if (DirectionX) {
		XY = FVector(1.f, 0.f, 0.f);
	}
	else {
		XY = FVector(0.f, 1.f, 0.f);
	}
	GetCapsuleComponent()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));
}

void AFlyingMob::Direction()
{
	if (FMath::IsNearlyEqual(GetCapsuleComponent()->GetRelativeLocation().X, Length, 10.0f)) {
		Length = Length * (-1);
		XY = XY * (-1);
		GetCapsuleComponent()->SetRelativeRotation(GetCapsuleComponent()->GetRelativeRotation() * (-1));
	}
}

// Called every frame
void AFlyingMob::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AddMovementInput(XY, Speed);

	Direction();
}

