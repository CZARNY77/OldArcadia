// Fill out your copyright notice in the Description page of Project Settings.


#include "Spikes.h"
#include "Gracz2.h"
#include "Components/BoxComponent.h"

// Sets default values
ASpikes::ASpikes()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DummyRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Dummy0"));
	RootComponent = DummyRoot;

	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("BOX"));
	Box->SetCollisionProfileName("Trigger");
	Box->SetupAttachment(DummyRoot);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(DummyRoot);

	Box->OnComponentBeginOverlap.AddDynamic(this, &ASpikes::OnOverlapBegin);

}

// Called when the game starts or when spawned
void ASpikes::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASpikes::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASpikes::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (AGracz2* Gracz = Cast<AGracz2>(OtherActor)) {
		Gracz->TakeDamage();
	}
}

