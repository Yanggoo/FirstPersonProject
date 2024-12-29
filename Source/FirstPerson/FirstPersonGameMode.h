// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FirstPersonGameMode.generated.h"

UCLASS(minimalapi)
class AFirstPersonGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AFirstPersonGameMode();
	virtual void BeginPlay() override;
	void EndGame();
	virtual void Tick(float DeltaSeconds) override;
	void PostLogin(APlayerController* NewPlayer) override;

private:
	TArray<AActor*> Cubes;
	
};



