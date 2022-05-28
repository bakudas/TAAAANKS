// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Bullet.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

/**
 * @TankPlayerClass 
 */
ATank::ATank()
{
	// Setup Spring Arm Component and Attach to the root
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);

	// Create and setup Camera Component and Attach to Spring Arm
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
}


// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();

	// Cast Controller as Player Controller
	PlayerController = Cast<APlayerController>(GetController());
	
}

// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (PlayerController)
	{
		FHitResult HitResult; // Hit var
		
		// Get hit mouse location
		PlayerController->GetHitResultUnderCursor(ECollisionChannel::ECC_Camera, false, HitResult);
		
		// Draw a debug sphere to see the location of mouse position in the world
		DrawDebugSphere(
			this->GetWorld(),
			HitResult.Location,
			100.f,
			12.f,
			FColor(.8f,0,1,255),
			false,
			0,
			0,
			5.f);
		
		// Call fuction to rotate the turret canon
		RotateTurret(HitResult.Location);
	}

}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Action Mapping
	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &ATank::FireProjectile);
	
	// Axis Mapping
	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATank::Move);
	PlayerInputComponent->BindAxis(TEXT("TurnRate"), this, &ATank::BaseTurn);
}

// Forward Movement method
auto ATank::Move(float Value) -> void
{
	// Create and initialized a VectorZero
	FVector DeltaLocation = FVector::ZeroVector;

	// Set X value with value normalized by deltatime 
	DeltaLocation.X = Value * MovementSpeed * UGameplayStatics::GetWorldDeltaSeconds(this);

	// Add an Offset Location to current position and grant sweep mode as well
	AddActorLocalOffset(DeltaLocation, true);
}

// Steering tank base
auto ATank::BaseTurn(float Value) -> void
{
	// Create a initialized a Rotator with zero vector
	FRotator DeltaRotation = FRotator::ZeroRotator;

	// Set Yaw Rotator with value normalized by deltatime (GameplayStatics Library)
	DeltaRotation.Yaw = Value * TurnRate * UGameplayStatics::GetWorldDeltaSeconds(this);

	// Add value to curret rotation and grant sweep mode as well
	AddActorLocalRotation(DeltaRotation, true);
}

// Fire Projectiles
auto ATank::FireProjectile() -> void
{
	// TODO Spawn projectile from cpp
	UE_LOG(LogTemp, Warning, TEXT("PEW")); // PEW PEW PEW
}

// Rotating the tank turret
auto ATank::RotateTurret(FVector &TargetLocation) -> void
{
	// Get and set Start location 
	const FVector StartLocation = TurretMesh->GetComponentLocation();

	// Perform a method FindLookAtRotation -> Kismet Math Library and set Rotator with the result
	const FRotator LookAtTargetRotation = UKismetMathLibrary::FindLookAtRotation(StartLocation, TargetLocation);

	// Set Turret relative location to new Yaw value 
	TurretMesh->SetRelativeRotation(FRotator(0,LookAtTargetRotation.Yaw,0));
}
