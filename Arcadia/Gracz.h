#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Gracz.generated.h"

UCLASS()
class ARCADIA_API AGracz : public APawn
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Mesh")
	class UStaticMeshComponent* MainMesh;

	UPROPERTY(EditAnywhere, Category = "Camera")
	class USpringArmComponent* SpringArm;
	UPROPERTY(EditAnywhere, Category = "Camera")
	class UCameraComponent* Camera;
public:
	AGracz();

protected:
	virtual void BeginPlay() override;

	void MoveRight(float Val);
	void Jump(float Val);
public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
