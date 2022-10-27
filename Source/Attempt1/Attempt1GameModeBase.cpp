// Copyright Epic Games, Inc. All Rights Reserved.


#include "Attempt1GameModeBase.h"
#include "MyPlayerController.h"
#include "MyPawn.h"


AAttempt1GameModeBase::AAttempt1GameModeBase() {
	PlayerControllerClass = AMyPlayerController::StaticClass();
	DefaultPawnClass = AMyPawn::StaticClass();
}
