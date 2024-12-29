// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "FirstPersonGameState.generated.h"

/**
 * 
 */
UCLASS()
class FIRSTPERSON_API AFirstPersonGameState : public AGameStateBase
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Game Settings")
	int32 NumOfImportantCubes;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Game Settings")
	float GameDuration;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Game Settings")
	int32 XPoints;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Game Settings")
	float YScale;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Game Settings")
	uint8 PlayerCapacity;
	UFUNCTION()
	void OnRep_Time(float CurrentTime) const{
		TimeUpdateDelegate.Broadcast(GameDuration-CurrentTime);
	}
	UPROPERTY(ReplicatedUsing = OnRep_Time, BlueprintReadWrite, Category = "Game Infos")
	float GlobalTime;
public:
	AFirstPersonGameState();
	float GetGlobalTime() const {return GlobalTime;}
	void SetGlobalTime(const float NewGlobalTime){GlobalTime = NewGlobalTime;}
	uint8 GetPlayerVelocity() const {return PlayerCapacity;}
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	int32 GetNumOfImportantCubes() const
	{
		return NumOfImportantCubes;
	}

	float GetGameDuration() const
	{
		return GameDuration;
	}

	int32 GetXPoints() const
	{
		return XPoints;
	}

	float GetYScale() const
	{
		return YScale;
	}

	DECLARE_MULTICAST_DELEGATE_OneParam(FTimeUpdate, float);
	FTimeUpdate TimeUpdateDelegate;
};
