// Fill out your copyright notice in the Description page of Project Settings.

#include "MyPawn.h"
#include "GrabberComponent.h"

AMyPawn::AMyPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	Grabber = CreateDefaultSubobject<UGrabberComponent>(TEXT("Grabber"));
}

void AMyPawn::BeginPlay()
{
	Super::BeginPlay();
}

void AMyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AMyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Grab", IE_Pressed, Grabber, &UGrabberComponent::GrabCallback);
	PlayerInputComponent->BindAction("Grab", IE_Released, Grabber, &UGrabberComponent::ReleaseCallback);
}

