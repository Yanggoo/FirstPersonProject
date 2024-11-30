// Fill out your copyright notice in the Description page of Project Settings.


#include "FirstPersonGameState.h"

#include "Net/UnrealNetwork.h"


AFirstPersonGameState::AFirstPersonGameState()
{
	GlobalTime = 0.0f;
	NumOfImportantCubes = 3;
	GameDuration = 60.0f;
	XPoints = 1;
	YScale = 0.5;
}

void AFirstPersonGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AFirstPersonGameState, GlobalTime);
}
