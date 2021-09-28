// Fill out your copyright notice in the Description page of Project Settings.


#include "KeyToGate.h"
#include "Gracz2.h"
#include "Gate.h"
#include "Components/SphereComponent.h"

// Sets default values
AKeyToGate::AKeyToGate()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	Sphere->InitSphereRadius(32.f);
	Sphere->SetCollisionProfileName("Trigger");

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;
	Sphere->SetupAttachment(Mesh);

	Sphere->OnComponentBeginOverlap.AddDynamic(this, &AKeyToGate::OnOverlapBegin);
}

// Called when the game starts or when spawned
void AKeyToGate::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AKeyToGate::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector MoveDelta = (FVector(0.f, 0.f, 8.f) * (FMath::Sin(GetWorld()->GetTimeSeconds() + DeltaTime) - FMath::Sin(GetWorld()->GetTimeSeconds())));
	AddActorWorldOffset(MoveDelta, true);

}

void AKeyToGate::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (AGracz2* Gracz = Cast<AGracz2>(OtherActor)) {
		if (Gate) {
			Gate->Keys++;
		}
		this->Destroy();
	}
}

