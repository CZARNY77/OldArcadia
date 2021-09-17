// Fill out your copyright notice in the Description page of Project Settings.


#include "Teleport.h"
#include "Gracz2.h"
#include "Components/BoxComponent.h"
#include "DrawDebugHelpers.h"

// Sets default values
ATeleport::ATeleport()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DummyRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Dummy0"));
	RootComponent = DummyRoot;

	Box_1 = CreateDefaultSubobject<UBoxComponent>(TEXT("BOX_1"));
	Box_1->InitBoxExtent(FVector(50, 50, 50));
	Box_1->SetCollisionProfileName("Trigger");
	Box_1->SetupAttachment(DummyRoot);

	Box_2 = CreateDefaultSubobject<UBoxComponent>(TEXT("BOX_2"));
	Box_2->InitBoxExtent(FVector(50, 50, 50));
	Box_2->SetCollisionProfileName("Trigger");
	Box_2->SetupAttachment(DummyRoot);

	Mesh_1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh_1"));
	Mesh_1->SetupAttachment(Box_1);

	Mesh_2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh_2"));
	Mesh_2->SetupAttachment(Box_2);
}

// Called when the game starts or when spawned
void ATeleport::BeginPlay()
{
	Super::BeginPlay();
	
	Box_1->OnComponentBeginOverlap.AddDynamic(this, &ATeleport::OnOverlapBox_1);
	Box_1->OnComponentEndOverlap.AddDynamic(this, &ATeleport::OnOverlapEnd);

	Box_2->OnComponentBeginOverlap.AddDynamic(this, &ATeleport::OnOverlapBox_2);
	Box_2->OnComponentEndOverlap.AddDynamic(this, &ATeleport::OnOverlapEnd);
	DrawDebugBox(GetWorld(), Box_1->GetComponentLocation(), Box_1->GetScaledBoxExtent(), FQuat(GetActorRotation()), FColor::Turquoise, true, -1, 0, 2);
	DrawDebugBox(GetWorld(), Box_2->GetComponentLocation(), Box_2->GetScaledBoxExtent(), FQuat(GetActorRotation()), FColor::Turquoise, true, -1, 0, 2);
}

// Called every frame
void ATeleport::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATeleport::TepPlayer()
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Tep"));
	if (Box)	Gracz->SetActorLocation(Box_2->K2_GetComponentLocation());
	else		Gracz->SetActorLocation(Box_1->K2_GetComponentLocation());
}

void ATeleport::OnOverlapBox_1(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Gracz = Cast<AGracz2>(OtherActor);
	if (Gracz) {
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, TEXT("Wszedl do teleportu"));
		Gracz->Teleport = this;
		Box = true;
	}
}

void ATeleport::OnOverlapBox_2(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Gracz = Cast<AGracz2>(OtherActor);
	if (Gracz) {
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, TEXT("Wszedl do teleportu"));
		Gracz->Teleport = this;
		Box = false;
	}
}

void ATeleport::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Gracz = Cast<AGracz2>(OtherActor);
	if (Gracz) {
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, TEXT("Wyszedl z teleportu"));
		Gracz->Teleport = NULL;
	}
}

