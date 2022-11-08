// Fill out your copyright notice in the Description page of Project Settings.


#include "OrbitCameraActor.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
AOrbitCameraActor::AOrbitCameraActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));

	UCameraComponent* TempCameraComponent = FindComponentByClass<UCameraComponent>();

	TempCameraComponent->AttachToComponent(SpringArmComponent, FAttachmentTransformRules::KeepRelativeTransform);

	YawSpeed = 10;
	PitchSpeed = 10;
	MinPitchAngle = -60.0f;
	MaxPitchAngle = 60.0f;

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

	FRotator Rotation = SpringArmComponent->GetRelativeRotation();

	Rotation.Pitch = FMath::Clamp(Rotation.Pitch + Val * PitchSpeed, MinPitchAngle, MaxPitchAngle);

	SpringArmComponent->SetRelativeRotation(Rotation);
}

void AOrbitCameraActor::AddControllerYawInput(float Val)
{
	if (!Interacting) return;

	FRotator Rotation = SpringArmComponent->GetRelativeRotation();

	Rotation.Yaw += Val * YawSpeed;

	SpringArmComponent->SetRelativeRotation(Rotation);
}

#if WITH_EDITOR
void AOrbitCameraActor::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	MinPitchAngle = FMath::Clamp(MinPitchAngle, -180.0f, .0f);
	MaxPitchAngle = FMath::Clamp(MaxPitchAngle, .0f, 180.0f);
}
#endif

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
