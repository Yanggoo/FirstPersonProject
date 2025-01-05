// Copyright Epic Games, Inc. All Rights Reserved.

#include "FirstPersonGameMode.h"

#include "EngineUtils.h"
#include "FirstPersonCharacter.h"
#include "FirstPersonGameState.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"
#include "TargetedCube.h"
#include "FirstPersonPlayerController.h"
#include "FirstPersonPlayerState.h"

AFirstPersonGameMode::AFirstPersonGameMode()
	: Super()
{
	PrimaryActorTick.bCanEverTick = true;
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(
		TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	//Set player states
	PlayerStateClass = AFirstPersonPlayerState::StaticClass();

	//Set game state
	GameStateClass = AFirstPersonGameState::StaticClass();
}

void AFirstPersonGameMode::BeginPlay()
{
	if (HasAuthority())
	{
		Super::BeginPlay();
		AFirstPersonGameState* FirstPersonGameState = GetGameState<AFirstPersonGameState>();
		checkf(FirstPersonGameState, TEXT("No available game state"));
		//Get all cubes in the scene
		Cubes.Empty();
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATargetedCube::StaticClass(), Cubes);
		//Mark important cubes
		for (int32 i = 0; i < FirstPersonGameState->GetNumOfImportantCubes() && i < Cubes.Num(); i++)
		{
			int32 index = FMath::RandRange(0, Cubes.Num() - 1);
			if (ATargetedCube* pCube = Cast<ATargetedCube>(Cubes[index]))
			{
				if (pCube->IsImportant())
				{
					i--;
				}
				else
				{
					pCube->SetImportant();
				}
			}
		}

		//Set global time
		FirstPersonGameState->SetGlobalTime(0.0f);
	}
}

void AFirstPersonGameMode::EndGame()
{
	if (HasAuthority())
	{
		UE_LOG(LogTemp, Log, TEXT("Game End!"));
		for (AFirstPersonPlayerController* PC : TActorRange<AFirstPersonPlayerController>(GetWorld()))
		{
			UE_LOG(LogTemp, Log, TEXT("Player %s Score: %d"), *PC->GetName(), PC->GetScore());
		}
		UKismetSystemLibrary::QuitGame(GetWorld(), nullptr, EQuitPreference::Quit, true);
	}
}

void AFirstPersonGameMode::Tick(float DeltaSeconds)
{
	if (HasAuthority())
	{
		AFirstPersonGameState* FirstPersonGameState = GetGameState<AFirstPersonGameState>();
		if(GetNumPlayers()==FirstPersonGameState->GetPlayerVelocity())
		{
			Super::Tick(DeltaSeconds);
			
			float CurrentGlobalTime = FirstPersonGameState->GetGlobalTime() + DeltaSeconds;
			if(floor(CurrentGlobalTime)!=floor(FirstPersonGameState->GetGlobalTime()))
			{
				FirstPersonGameState->TimeUpdateDelegate.Broadcast(FirstPersonGameState->GetGameDuration() - CurrentGlobalTime);
			}
			FirstPersonGameState->SetGlobalTime(CurrentGlobalTime);
			if (CurrentGlobalTime >= FirstPersonGameState->GetGameDuration())
			{
				// EndGame();
			}
		}
	}
}

void AFirstPersonGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
	if(AFirstPersonPlayerController* PC=Cast<AFirstPersonPlayerController>(NewPlayer))
	{
		PC->SendNewPLayerName();
	}
}
