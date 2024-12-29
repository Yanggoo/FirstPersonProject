// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/PlayerState.h"
#include "FirstPersonGameState.h"
#include "FirstPersonPlayerController.generated.h"


class UInputMappingContext;

/**
 *
 */
UCLASS()
class FIRSTPERSON_API AFirstPersonPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:

	/** Input Mapping Context to be used for player input */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputMappingContext* InputMappingContext;
	FTimerHandle TimerHandle;

	// Begin Actor interface
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	TArray<Chaos::Pair<int32,FString>>PlayerIdAndName;
	bool BInitialized=false;
public:
	void InitializeName();
	int32 GetScore()const;
	void AddScore(int32 Value);
	DECLARE_MULTICAST_DELEGATE(FCrosshairUpdate);
	FCrosshairUpdate CrosshairUpdate;
	DECLARE_MULTICAST_DELEGATE_TwoParams(FBulletUpdate, uint8, uint8);
	FBulletUpdate BulletUpdateDelegate;
	UFUNCTION(Server, Reliable)
	void ServerUpdatePlayerName(int32 PlayerId,const FString& NewName);
	void UpdatePlayerName();
	UFUNCTION(Client,Unreliable)
	void SendNewPLayerName();
	// End Actor interface
};
