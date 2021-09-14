// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Corner.h"
#include "GameFramework/Character.h"
#include "Gracz2.generated.h"

UCLASS()
class ARCADIA_API AGracz2 : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Camera")
	class USpringArmComponent* SpringArm;
	UPROPERTY(EditAnywhere, Category = "Camera")
	class UCameraComponent* Camera;

	void MoveRight(float Val);

	UFUNCTION()
	void Action();

	float X;
	float Y;
	float Yaw;
	FRotator EndR;
public:
	// Sets default values for this character's properties
	AGracz2();

	class ACorner* Corner;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
		void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};