// Fill out your copyright notice in the Description page of Project Settings.


#include "Corner.h"
#include "Components/BoxComponent.h"

// Sets default values
ACorner::ACorner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DummyRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Dummy0"));
	RootComponent = DummyRoot;

	MeshBox = CreateDefaultSubobject<UBoxComponent>(TEXT("MeshBox"));
	MeshBox->SetupAttachment(DummyRoot);

	MeshBox->OnComponentBeginOverlap.AddDynamic(this, &ACorner::OnOverlapBox);

}

// Called when the game starts or when spawned
void ACorner::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACorner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACorner::OnOverlapBox(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

}

