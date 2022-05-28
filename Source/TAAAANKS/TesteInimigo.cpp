// Fill out your copyright notice in the Description page of Project Settings.


#include "TesteInimigo.h"
#include "Components/CapsuleComponent.h"
#include "Components/InterpToMovementComponent.h"
#include "Components/ArrowComponent.h"


// Sets default values
ATesteInimigo::ATesteInimigo()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create and Setup a Capsulle Component and set as rootcomponent
	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComp"));
	RootComponent = CapsuleComponent;

	// Create and Setup a Base Mesh to Actor
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(CapsuleComponent);

	// Create and Setup Arrow Component 
	ArrowComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	ArrowComponent->SetupAttachment(CapsuleComponent);

	// Create and Setup Interp Moviment Component
	InterpToMovementComponent = CreateDefaultSubobject<UInterpToMovementComponent>(TEXT("InterptoMove"));
	InterpToMovementComponent->SetUpdatedComponent(CapsuleComponent);

	ControlPoints.Add(StartPoint);
	ControlPoints.Add(EndPoint);
	
	SetupMovement(ControlPoints, EInterpToBehaviourType::PingPong);
	
	// Binding Event to Delegate
	//InterpToMovementComponent->OnInterpToReverse.AddDynamic(this, &ATesteInimigo::OnInterpToReverse);

}

// Called when the game starts or when spawned
void ATesteInimigo::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATesteInimigo::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (InterpToMovementComponent->Velocity.X > 0)
	{
		BaseMesh->SetRelativeScale3D(FVector(-3, 3, 3));
	}
	else if (InterpToMovementComponent->Velocity.X < 0)
	{
		BaseMesh->SetRelativeScale3D(FVector(3, 3, 3));
	}

	UInterpToMovementComponent::FOnInterpToReverseDelegate ReverseMove = InterpToMovementComponent->OnInterpToReverse;
	
}


// Initial Setup to InterpToMovement Comp
void ATesteInimigo::SetupMovement(TArray<FVector> Points, EInterpToBehaviourType BehaviorType) const
{
	// Add control point to movement vector
	InterpToMovementComponent->AddControlPointPosition(Points[0], true);
	InterpToMovementComponent->AddControlPointPosition(Points[1], true);

	// Update Vector with new points
	InterpToMovementComponent->FinaliseControlPoints();

	// Set behavior type to movement
	InterpToMovementComponent->BehaviourType = BehaviorType;
}
