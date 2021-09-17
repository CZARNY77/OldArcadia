// Fill out your copyright notice in the Description page of Project Settings.


#include "Corner.h"
#include "Gracz2.h"
#include "Components/BoxComponent.h"
#include "DrawDebugHelpers.h"

// Sets default values
ACorner::ACorner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DummyRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Dummy0"));
	RootComponent = DummyRoot;

	MeshBox = CreateDefaultSubobject<UBoxComponent>(TEXT("MeshBox"));
	MeshBox->InitBoxExtent(FVector(50, 50, 50));
	MeshBox->SetCollisionProfileName("Trigger");
	MeshBox->SetupAttachment(DummyRoot);

	MeshBox->OnComponentBeginOverlap.AddDynamic(this, &ACorner::OnOverlapBox);

	IsInCorner = false;
}

// Called when the game starts or when spawned
void ACorner::BeginPlay()
{
	Super::BeginPlay();

	MeshBox->OnComponentEndOverlap.AddDynamic(this, &ACorner::OnOverlapEnd);
	DrawDebugBox(GetWorld(), GetActorLocation(), MeshBox->GetScaledBoxExtent(), FQuat(GetActorRotation()), FColor::Turquoise, true, -1, 0, 2);
}

// Called every frame
void ACorner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACorner::OnOverlapBox(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (AGracz2* Gracz = Cast<AGracz2>(OtherActor)) {
		Gracz->Corner = this;
	}
}

void ACorner::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (AGracz2* Gracz = Cast<AGracz2>(OtherActor)) {
		Gracz->Corner = NULL;
	}
}

