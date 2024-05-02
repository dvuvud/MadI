// Fill out your copyright notice in the Description page of Project Settings.


#include "MadlChar.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Net/UnrealNetwork.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Components/CapsuleComponent.h"

AMadlChar::AMadlChar()
{
	PrimaryActorTick.bCanEverTick = true;
	SpawnCollisionHandlingMethod = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetMesh());
	CameraBoom->TargetArmLength = 360;
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	bUseControllerRotationYaw = false;
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	UCharacterMovementComponent* const MovementComponent = GetCharacterMovement();
	if (MovementComponent){
		MovementComponent->bOrientRotationToMovement = true;
		MovementComponent->bUseControllerDesiredRotation = false;
		}

	GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);
	GetCharacterMovement()->RotationRate = FRotator(0.f, 0.f, 660.f);
	NetUpdateFrequency = 66.f;
	MinNetUpdateFrequency = 33.f;
}

void AMadlChar::BeginPlay()
{
	Super::BeginPlay();
	
	MadlPlayerController = Cast<APlayerController>(GetController());
	if (MadlPlayerController)
	{
		
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(MadlPlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(MadlMappingContext, 0);
		}
	}
}

void AMadlChar::Move(const FInputActionValue& Value)
{
	if (Controller)
	{
		const FVector2D UnitVector = Value.Get<FVector2D>();
		const FRotator UnitRotation(0, Controller->GetControlRotation().Yaw, 0);
		if (UnitVector.Y != 0.f)
		{
			const FVector Direction = UnitRotation.RotateVector(FVector::ForwardVector);

			AddMovementInput(Direction, UnitVector.Y);
		}

		if (UnitVector.X != 0.f)
		{
			const FVector Direction = UnitRotation.RotateVector(FVector::RightVector);
	
			AddMovementInput(Direction, UnitVector.X);
		}
	}
}

void AMadlChar::Look(const FInputActionValue& Value)
{
	if (Controller)
	{
		const FVector2D LookValue = Value.Get<FVector2D>();
		if (LookValue.X != 0.f)
		{
			AddControllerYawInput(LookValue.X * MouseSensitivity);
		}
		if (LookValue.Y != 0.f)
		{
			AddControllerPitchInput(LookValue.Y * MouseSensitivity);
		}
	}
}

void AMadlChar::NoGravity()
{
	ToggleGravityOnAndOffInteger++;
	bool bToggle = ToggleGravityOnAndOffInteger % 2 > 0 ? true : false;
	UCharacterMovementComponent* MovementComp = GetCharacterMovement();


	if (bToggle && MovementComp)
	{
		MovementComp->GravityScale = 0;
	}
	else if (MovementComp)
	{
		MovementComp->GravityScale = 1;
	}
}

void AMadlChar::Jump()
{
	Super::Jump();
}

void AMadlChar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void AMadlChar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMadlChar::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AMadlChar::Look);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &AMadlChar::Jump);
		EnhancedInputComponent->BindAction(NoGravityAction, ETriggerEvent::Started, this, &AMadlChar::NoGravity);
	}
}

