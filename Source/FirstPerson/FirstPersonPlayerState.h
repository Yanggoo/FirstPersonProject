// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "FirstPersonPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class FIRSTPERSON_API AFirstPersonPlayerState : public APlayerState
{
	GENERATED_BODY()

protected:
	UPROPERTY(ReplicatedUsing=OnRep_PlayerScore)
	int32 PlayerScore;
	UFUNCTION()
	void OnRep_PlayerScore();

public:
	AFirstPersonPlayerState();
	UFUNCTION(BlueprintCallable)
	inline int32 GetPlayerScore() const { return PlayerScore; }
	inline void AddPlayerScore(const int32 Value) { PlayerScore += Value; }
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
