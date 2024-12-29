// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "FirstPersonGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class FIRSTPERSON_API UFirstPersonGameInstance : public UGameInstance
{
	GENERATED_BODY()
protected:
	FString PlayerName;
public:
	UFUNCTION(BlueprintCallable)
	void SetPlayerName(FString Name)
	{
		PlayerName = Name;
	}
	UFUNCTION(BlueprintCallable)
	FString GetPlayerName()
	{
		return PlayerName;
	}
};
