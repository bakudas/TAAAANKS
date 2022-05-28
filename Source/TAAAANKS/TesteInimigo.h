// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/InterpToMovementComponent.h"
#include "GameFramework/Pawn.h"
#include "TesteInimigo.generated.h"



UCLASS()
class TAAAANKS_API ATesteInimigo : public APawn
{
	GENERATED_BODY()

public:

	//DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnInterpToReverseDelegate, const FHitResult&, ImpactResult, const float, Time);
	
	// Sets default values for this pawn's properties
	ATesteInimigo();

protected:
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	//FOnInterpToReverseDelegate OnInterpToReverse;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess))
	class UCapsuleComponent* CapsuleComponent;

	UPROPERTY(EditAnywhere,  BlueprintReadWrite, meta=(AllowPrivateAccess))
	class UArrowComponent* ArrowComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess))
	TArray<FVector> ControlPoints;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* BaseMesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UInterpToMovementComponent* InterpToMovementComponent;
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector StartPoint = FVector(-200, 0, 0);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector EndPoint = FVector(200, 0, 0);

	void SetupMovement(TArray<FVector> Points, EInterpToBehaviourType BehaviorType) const;

};
