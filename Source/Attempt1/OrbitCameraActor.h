// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraActor.h"
#include "OrbitCameraActor.generated.h"

UCLASS()
class ATTEMPT1_API AOrbitCameraActor : public ACameraActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AOrbitCameraActor(const FObjectInitializer&);

	UPROPERTY(VisibleAnywhere)
	float YawSpeed;

	UPROPERTY(VisibleAnywhere)
	float PitchSpeed;

private:

	/** The camera component for this camera */
	UPROPERTY(Category = CameraActor, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* SpringArmComponent;

	bool Interacting;

protected:

	virtual void BeginPlay() override;

	UFUNCTION()
	void PressedCallback();

	UFUNCTION()
	void ReleasedCallback();

	UFUNCTION()
	void BindToInput();

	UFUNCTION()
	void AddControllerPitchInput(float Val);

	UFUNCTION()
	void AddControllerYawInput(float Val);

};
