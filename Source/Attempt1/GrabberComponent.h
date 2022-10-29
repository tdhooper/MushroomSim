// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "GrabberComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ATTEMPT1_API UGrabberComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	UPROPERTY()
	APlayerController* PlayerController;

	UPROPERTY(VisibleAnywhere)
	UPhysicsHandleComponent* PhysicsHandle = nullptr;

	UPROPERTY()
	float GrabStartDepth;

	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Sets default values for this component's properties
	UGrabberComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;	

	UFUNCTION()
	void GrabCallback();

	UFUNCTION()
	void ReleaseCallback();

};
