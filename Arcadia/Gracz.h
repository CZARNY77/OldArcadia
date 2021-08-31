#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Gracz.generated.h"

UCLASS()
class ARCADIA_API AGracz : public APawn
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Mesh")
	class UCapsuleComponent* MainCap;

	//UPROPERTY(EditAnywhere, Category = "Mesh")
	//class UPaperFlipbook* SourceFlipbook;

	//UPROPERTY(EditAnywhere, Category = "Mesh")
	//class UStaticMeshComponent* MainMesh;

	UPROPERTY(EditAnywhere, Category = "Camera")
	class USpringArmComponent* SpringArm;
	UPROPERTY(EditAnywhere, Category = "Camera")
	class UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, Category = "Move")
	float Speed;
	UPROPERTY(EditAnywhere, Category = "Move")
	float Up;

	float MaxSpeed;
	bool pJump;
public:
	AGracz();

protected:
	virtual void BeginPlay() override;

	void MoveRight(float Val);
	void Jump();
public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
