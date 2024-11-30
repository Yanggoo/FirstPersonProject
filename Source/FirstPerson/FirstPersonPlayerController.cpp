// Copyright Epic Games, Inc. All Rights Reserved.


#include "FirstPersonPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "FirstPersonPlayerState.h"
#include "Engine/LocalPlayer.h"

void AFirstPersonPlayerController::BeginPlay()
{
	Super::BeginPlay();
	// get the enhanced input subsystem
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(
		GetLocalPlayer()))
	{
		// add the mapping context so we get controls
		Subsystem->AddMappingContext(InputMappingContext, 0);
	}
}

int32 AFirstPersonPlayerController::GetScore() const
{
	AFirstPersonPlayerState* FirstPersonPlayerState = GetPlayerState<AFirstPersonPlayerState>();
	return FirstPersonPlayerState->GetPlayerScore();
}

void AFirstPersonPlayerController::AddScore(int32 Value)
{
	AFirstPersonPlayerState* FirstPersonPlayerState = GetPlayerState<AFirstPersonPlayerState>();
	FirstPersonPlayerState->AddPlayerScore(Value);
	
}
