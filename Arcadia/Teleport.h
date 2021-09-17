// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gracz2.h"
#include "GameFramework/Actor.h"
#include "Teleport.generated.h"

UCLASS()
class ARCADIA_API ATeleport : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Components")
	class USceneComponent* DummyRoot;

	UPROPERTY(EditAnywhere, Category = "Components")
	class UBoxComponent* Box_1;

	UPROPERTY(EditAnywhere, Category = "Components")
	class UBoxComponent* Box_2;

	UPROPERTY(EditAnywhere, Category = "Components")
	class UStaticMeshComponent* Mesh_1;

	UPROPERTY(EditAnywhere, Category = "Components")
	class UStaticMeshComponent* Mesh_2;

	bool Box;
public:	
	// Sets default values for this actor's properties
	ATeleport();

	UFUNCTION()
	void TepPlayer();

	class AGracz2* Gracz;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnOverlapBox_1(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnOverlapBox_2(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
