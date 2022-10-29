// Fill out your copyright notice in the Description page of Project Settings.


#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "OrbitCameraActor.h"

// Sets default values
AOrbitCameraActor::AOrbitCameraActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));

	UCameraComponent* TempCameraComponent = FindComponentByClass<UCameraComponent>();

	TempCameraComponent->AttachToComponent(SpringArmComponent, FAttachmentTransformRules::KeepRelativeTransform);

	YawSpeed = 10;
	PitchSpeed = 10;

	Interacting = false;
}

void AOrbitCameraActor::BeginPlay()
{
	Super::BeginPlay();

	BindToInput();
}

void AOrbitCameraActor::PressedCallback()
{
	Interacting = true;
}

void AOrbitCameraActor::ReleasedCallback()
{
	Interacting = false;
}


void AOrbitCameraActor::AddControllerPitchInput(float Val)
{
	if (!Interacting) return;

	FRotator Rotation = GetActorRotation();

	Rotation.Pitch += Val * PitchSpeed;

	SetActorRotation(Rotation);
}

void AOrbitCameraActor::AddControllerYawInput(float Val)
{
	if (!Interacting) return;

	FRotator Rotation = GetActorRotation();

	Rotation.Yaw += Val * YawSpeed;

	SetActorRotation(Rotation);
}

void AOrbitCameraActor::BindToInput()
{
	InputComponent = NewObject<UInputComponent>(this);
	InputComponent->RegisterComponent();

	if (InputComponent)
	{
		InputComponent->BindAction("OrbitCamera", IE_Pressed, this, &AOrbitCameraActor::PressedCallback);
		InputComponent->BindAction("OrbitCamera", IE_Released, this, &AOrbitCameraActor::ReleasedCallback);
		InputComponent->BindAxis("OrbitCameraX", this, &AOrbitCameraActor::AddControllerYawInput);
		InputComponent->BindAxis("OrbitCameraY", this, &AOrbitCameraActor::AddControllerPitchInput);

		EnableInput(GetWorld()->GetFirstPlayerController());
	}
}
