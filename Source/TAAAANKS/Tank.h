// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tank.generated.h"

/**
 * 
 */
UCLASS()
class TAAAANKS_API ATank : public ABasePawn
{
	GENERATED_BODY()

public:
	ATank();
	
	void RotateTurret(FVector& TargetLocation);

private:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess))
	float MovementSpeed = 200.0f;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components", meta=(AllowPrivateAccess))
	class USpringArmComponent* SpringArm;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components", meta=(AllowPrivateAccess))
	class UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess))
	UBlueprint* Bullet;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess))
	APlayerController* PlayerController;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess))
	float TurnRate = 100.0f;
	
	
	void Move(float Value);
	
	void BaseTurn(float Value);
	
	void TurretTurn(float Value);
	
	void FireProjectile();

protected:
	virtual void BeginPlay() override;

	public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
};
