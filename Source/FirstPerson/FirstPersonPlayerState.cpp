// Fill out your copyright notice in the Description page of Project Settings.


#include "FirstPersonPlayerState.h"

#include "Net/UnrealNetwork.h"


void AFirstPersonPlayerState::OnRep_PlayerScore()
{
	UE_LOG(LogTemp, Log, TEXT("Score updated: %d"), PlayerScore);
	PlayerScoreUpdateDelegate.Broadcast();
}

void AFirstPersonPlayerState::OnRep_Health()
{
	UE_LOG(LogTemp, Log, TEXT("Health updated: %f"), Health);
	PlayerHealthUpdateDelegate.Broadcast(Health,MaxHealth);
}

AFirstPersonPlayerState::AFirstPersonPlayerState()
{
	PlayerScore = 0;
	Health = MaxHealth = 100;
}

void AFirstPersonPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AFirstPersonPlayerState, PlayerScore);
	DOREPLIFETIME(AFirstPersonPlayerState, Health);
}

void AFirstPersonPlayerState::TakeDamage(float Damage)
{
	Health -= Damage;
	if (Health < 0.0f)
	{
		Health = 0.0f;
	}
	PlayerHealthUpdateDelegate.Broadcast(Health,MaxHealth);
}
