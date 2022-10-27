// Fill out your copyright notice in the Description page of Project Settings.


#include "GrabberComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"


UGrabberComponent::UGrabberComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	PhysicsHandle = CreateDefaultSubobject<UPhysicsHandleComponent>(TEXT("PhysicsHandle"));
}

void UGrabberComponent::BeginPlay()
{
	Super::BeginPlay();

	PlayerController = GetWorld()->GetFirstPlayerController();
}

void UGrabberComponent::GrabCallback()
{
	FHitResult result;
	if (PlayerController->GetHitResultUnderCursorByChannel(UEngineTypes::ConvertToTraceType(ECC_PhysicsBody), true, result))
	{
		FVector grabLocation = result.ImpactPoint;

		FVector ViewLocation;
		FRotator ViewRotation;
		PlayerController->PlayerCameraManager->GetCameraViewPoint(ViewLocation, ViewRotation);

		GrabStartDepth = FVector::DotProduct(grabLocation - ViewLocation, ViewRotation.Vector());

		PhysicsHandle->GrabComponentAtLocation(result.GetComponent(), NAME_None, grabLocation);
	}
}

void UGrabberComponent::ReleaseCallback()
{
	if (PhysicsHandle->GetGrabbedComponent() == nullptr) {
		return;
	}

	PhysicsHandle->ReleaseComponent();
}

void UGrabberComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (PhysicsHandle->GetGrabbedComponent() == nullptr) {
		return;
	}

	FVector mouseWorldLocation;
	FVector mouseWorldDirection;
	PlayerController->DeprojectMousePositionToWorld(mouseWorldLocation, mouseWorldDirection);

	FVector ViewLocation;
	FRotator ViewRotation;
	PlayerController->PlayerCameraManager->GetCameraViewPoint(ViewLocation, ViewRotation);

	// Project mouse position onto plane at depth
	FVector newLocation = ViewLocation + mouseWorldDirection * GrabStartDepth / FVector::DotProduct(mouseWorldDirection, ViewRotation.Vector());

	PhysicsHandle->SetTargetLocation(newLocation);
}

