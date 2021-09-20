// Fill out your copyright notice in the Description page of Project Settings.


#include "Gate.h"
#include "Gracz2.h"
#include "Components/BoxComponent.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AGate::AGate()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DummyRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Dummy0"));
	RootComponent = DummyRoot;

	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("BOX"));
	Box->InitBoxExtent(FVector(50, 50, 100));
	Box->SetCollisionProfileName("Trigger");
	Box->SetupAttachment(DummyRoot);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(DummyRoot);

	Keys = 0;
	MaxKeys = 3;

	Box->OnComponentBeginOverlap.AddDynamic(this, &AGate::OnOverlapBegin);
}

// Called when the game starts or when spawned
void AGate::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AGate::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGate::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (AGracz2 * Gracz = Cast<AGracz2>(OtherActor)) {
		if (Keys == MaxKeys) {
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Black, TEXT("Wygrales"));
			UGameplayStatics::OpenLevel(this, "lvl_2");
		}
		else GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Black, FString::Printf(TEXT("Jeszcze nie %i/3"), Keys));
	}
}

