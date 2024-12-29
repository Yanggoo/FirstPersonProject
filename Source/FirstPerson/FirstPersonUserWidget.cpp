// Fill out your copyright notice in the Description page of Project Settings.


#include "FirstPersonUserWidget.h"

#include "FirstPersonGameState.h"
#include "FirstPersonPlayerController.h"
#include "FirstPersonPlayerState.h"
#include "GameFramework/GameState.h"


void UFirstPersonUserWidget::InitializeBindings()
{
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UFirstPersonUserWidget::CheckForNewPlayers, 1.0f, true);
}

void UFirstPersonUserWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UFirstPersonUserWidget::NativeOnInitialized()
{
	Super::NativeConstruct();
	GetWorld()->GetTimerManager().SetTimerForNextTick(this, &UFirstPersonUserWidget::InitializeBindings);
	BoundPlayerControllers.Empty();
	BoundPlayerStates.Empty();
	BoundedToCurrentPlayer = false;
}

void UFirstPersonUserWidget::CheckForNewPlayers()
{
	if (AFirstPersonGameState* GameState = GetWorld()->GetGameState<AFirstPersonGameState>())
	{
		for (APlayerState* PlayerState : GameState->PlayerArray)
		{
			if (AFirstPersonPlayerState* PS = Cast<AFirstPersonPlayerState>(PlayerState))
			{
				if (!BoundPlayerStates.Contains(PS))
				{
					PS->PlayerScoreUpdateDelegate.AddUObject(this, &UFirstPersonUserWidget::UpdatePlayerScores);
					PS->PlayerScoreUpdateDelegate.Broadcast();
					BoundPlayerStates.Add(PS);
				}
			}
		}
	}
	if (!BoundedToCurrentPlayer)
	{
		if (AFirstPersonPlayerState* FirstPersonPlayerState = Cast<AFirstPersonPlayerState>(
			GetOwningLocalPlayer()->GetPlayerController(GetWorld())->PlayerState))
		{
			if (AFirstPersonPlayerController
				* PlayerController = Cast<AFirstPersonPlayerController>(
					GetOwningLocalPlayer()->GetPlayerController(GetWorld())))
			{
				PlayerController->BulletUpdateDelegate.AddUObject(this, &UFirstPersonUserWidget::UpdateBullets);
				PlayerController->CrosshairUpdate.AddUObject(this,&UFirstPersonUserWidget::UpdateCrosshair);
				FirstPersonPlayerState->PlayerHealthUpdateDelegate.AddUObject(
					this, &UFirstPersonUserWidget::UpdateHealth);
				AFirstPersonGameState* GameState = GetWorld()->GetGameState<AFirstPersonGameState>();
				GameState->TimeUpdateDelegate.AddUObject(this, &UFirstPersonUserWidget::UpdateTime);
				BoundedToCurrentPlayer = true;
			}
		}
	}
}
