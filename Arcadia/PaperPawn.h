// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "PaperPawn.generated.h"

/**
 * 
 */
UCLASS()
class ARCADIA_API APaperPawn : public APaperCharacter
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Camera")
	class USpringArmComponent* SpringArm;
	UPROPERTY(EditAnywhere, Category = "Camera")
	class UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, Category = "Animations")
	class UPaperFlipbook* StandingAnimation;
	UPROPERTY(EditAnywhere, Category = "Animations")
	class UPaperFlipbook* RunningAnimation;
	UPROPERTY(EditAnywhere, Category = "Animations")
	class UPaperFlipbook* JumpingAnimation;

	void MoveRight(float Val);
	void UpdateCharacter();
	void UpdateAnimation();

	void StartedJump(const ETouchIndex::Type FingerIndex, const FVector Location);
	void StopedJump(const ETouchIndex::Type FingerIndex, const FVector Location);

public:
	APaperPawn();

	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
