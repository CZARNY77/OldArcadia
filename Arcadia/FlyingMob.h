// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FlyingMob.generated.h"

UCLASS()
class ARCADIA_API AFlyingMob : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Components")
	class USceneComponent* DummyRoot;

	UPROPERTY(EditAnywhere, Category = "Components")
	class UBoxComponent* Box;

public:
	// Sets default values for this character's properties
	AFlyingMob();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Mob")
	bool DirectionX;

	FVector XY;
	float Location;

	UPROPERTY(EditAnywhere, Category = "Mob")
	float Speed;

	UPROPERTY(EditAnywhere, Category = "Mob")
	float Length;

	void Direction();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
