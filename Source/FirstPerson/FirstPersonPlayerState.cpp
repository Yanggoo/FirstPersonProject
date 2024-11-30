// Fill out your copyright notice in the Description page of Project Settings.


#include "FirstPersonPlayerState.h"

#include "Net/UnrealNetwork.h"


void AFirstPersonPlayerState::OnRep_PlayerScore()
{
	UE_LOG(LogTemp, Log, TEXT("Score updated: %d"), PlayerScore);
}

AFirstPersonPlayerState::AFirstPersonPlayerState()
{
	PlayerScore = 0;
}

void AFirstPersonPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AFirstPersonPlayerState, PlayerScore);
}
