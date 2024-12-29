// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FirstPersonUserWidget.generated.h"
class AFirstPersonPlayerState;
class AFirstPersonPlayerController;
class UImage;
class UProgressBar;
class UTextBlock;
class UMultiLineEditableTextBox;
/**
 * 
 */
UCLASS()
class FIRSTPERSON_API UFirstPersonUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, Category=UI, meta=(BindWidget))
	UTextBlock* Time;
	UPROPERTY(BlueprintReadWrite, Category=UI, meta=(BindWidget))
	UMultiLineEditableTextBox* Scores;
	UPROPERTY(BlueprintReadWrite, Category=UI, meta=(BindWidget))
	UProgressBar* Health;
	UPROPERTY(BlueprintReadWrite, Category=UI, meta=(BindWidget))
	UTextBlock* Text_Health;
	UPROPERTY(BlueprintReadWrite, Category=UI, meta=(BindWidget))
	UTextBlock* Text_Bullets;
	UPROPERTY(BlueprintReadWrite, Category=UI, meta=(BindWidget))
	UImage* Crosshair;
	UFUNCTION(BlueprintImplementableEvent, Category=UI)
	void UpdateTime(float CurrentTime);
	UFUNCTION(BlueprintImplementableEvent, Category=UI)
	void UpdatePlayerScores();
	UFUNCTION(BlueprintImplementableEvent, Category=UI)
	void UpdateBullets(uint8 LoadedBulletNum,uint8 BulletNum);
	UFUNCTION(BlueprintImplementableEvent, Category=UI)
	void UpdateHealth(float CurrentHealth, float MaxHealth);
	UFUNCTION(BlueprintImplementableEvent, Category=UI)
	void UpdateCrosshair();
	void InitializeBindings();

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	virtual void NativeOnInitialized() override;
protected:
	TArray<AFirstPersonPlayerController*>BoundPlayerControllers;
	TArray<AFirstPersonPlayerState*>BoundPlayerStates;
	void CheckForNewPlayers();
	bool BoundedToCurrentPlayer;
};
