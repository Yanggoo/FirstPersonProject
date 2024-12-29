// Copyright Epic Games, Inc. All Rights Reserved.


#include "FirstPersonPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "FirstPersonPlayerState.h"
#include "Engine/LocalPlayer.h"
#include "FirstPersonGameInstance.h"
#include "SkeletalMeshAttributes.h"

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
	PlayerIdAndName.Empty();
	InitializeName();
}

void AFirstPersonPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if(!BInitialized)
	{
		InitializeName();
	}
	if(!PlayerIdAndName.IsEmpty())
	{
		UpdatePlayerName();
	}
}

void AFirstPersonPlayerController::InitializeName()
{
	if (UFirstPersonGameInstance* GameInstance = Cast<UFirstPersonGameInstance>(GetGameInstance()))
	{
		if (APlayerState* PS = GetPlayerState<APlayerState>())
		{
			GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
			int32 Id =PS->GetPlayerId();
			FString PlayerName = GameInstance->GetPlayerName();
			if(GetPlayerState<APlayerState>()->GetPlayerId()==Id&&GetPlayerState<APlayerState>()->GetPlayerName()!=PlayerName)
			{
				BInitialized=true;
				if(HasAuthority())
				{
					PlayerIdAndName.Add(Chaos::MakePair(Id,PlayerName));
				}else
				{
					ServerUpdatePlayerName(Id,GameInstance->GetPlayerName());
				}
			}
		}
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
	FirstPersonPlayerState->PlayerScoreUpdateDelegate.Broadcast();
}

void AFirstPersonPlayerController::UpdatePlayerName()
{
	for (const Chaos::Pair<int32, FString>& Pair : PlayerIdAndName)
	{
		int32 PlayerId = Pair.First;
		FString PlayerName = Pair.Second;
		if (AGameStateBase* GameState = GetWorld()->GetGameState())
		{
			for (APlayerState* PS : GameState->PlayerArray)
			{
				if (PS && PS->GetPlayerId() == PlayerId)
				{
					PS->SetPlayerName(PlayerName);
				}
			}
		}
	}
	PlayerIdAndName.Empty();
}

void AFirstPersonPlayerController::SendNewPLayerName_Implementation()
{
	InitializeName();
}

void AFirstPersonPlayerController::ServerUpdatePlayerName_Implementation(int32 PlayerId,const FString& NewName)
{
	PlayerIdAndName.Add(Chaos::MakePair(PlayerId,NewName));
	UpdatePlayerName();
}
