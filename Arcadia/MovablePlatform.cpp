// Fill out your copyright notice in the Description page of Project Settings.


#include "MovablePlatform.h"
#include "Components/BoxComponent.h"
#include "DrawDebugHelpers.h"

// Sets default values
AMovablePlatform::AMovablePlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DummyRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Dummy0"));
	RootComponent = DummyRoot;

	Box_1 = CreateDefaultSubobject<UBoxComponent>(TEXT("BOX_1"));
	Box_1->InitBoxExtent(FVector(50, 50, 10));
	Box_1->SetCollisionProfileName("Trigger");
	Box_1->SetupAttachment(DummyRoot);

	Box_2 = CreateDefaultSubobject<UBoxComponent>(TEXT("BOX_2"));
	Box_2->InitBoxExtent(FVector(50, 50, 10));
	Box_2->SetCollisionProfileName("Trigger");
	Box_2->SetupAttachment(DummyRoot);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(DummyRoot);

}

// Called when the game starts or when spawned
void AMovablePlatform::BeginPlay()
{
	Super::BeginPlay();
	
	DrawDebugBox(GetWorld(), Box_1->GetComponentLocation(), Box_1->GetScaledBoxExtent(), FQuat(GetActorRotation()), FColor::Turquoise, true, -1, 0, 2);
	DrawDebugBox(GetWorld(), Box_2->GetComponentLocation(), Box_2->GetScaledBoxExtent(), FQuat(GetActorRotation()), FColor::Turquoise, true, -1, 0, 2);
	
	Mesh->SetRelativeLocation(Box_2->GetRelativeLocation() / 2);
}

// Called every frame
void AMovablePlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector VDirection = (Box_2->GetComponentLocation() - Box_1->GetComponentLocation())/2;
	FVector MoveDelta = (VDirection * (FMath::Sin(GetWorld()->GetTimeSeconds() + DeltaTime) - FMath::Sin(GetWorld()->GetTimeSeconds())));
	Mesh->AddLocalOffset(MoveDelta, true);
}

