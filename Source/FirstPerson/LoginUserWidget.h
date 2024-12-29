// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LoginUserWidget.generated.h"

class UProgressBar;
class UButton;
class UEditableText;
/**
 * 
 */
UCLASS()
class FIRSTPERSON_API ULoginUserWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, Category=UI, meta=(BindWidget))
	UEditableText* EditableText_Name;
	UPROPERTY(BlueprintReadWrite, Category=UI, meta=(BindWidget))
	UEditableText* EditableText_PassWord;
	UPROPERTY(BlueprintReadWrite, Category=UI, meta=(BindWidget))
	UButton* Button_Login;
	UPROPERTY(BlueprintReadWrite, Category=UI, meta=(BindWidget))
	UProgressBar* ProgressBar;
	FTimerHandle TimerHandle;
	FText Name;
	virtual void NativeOnInitialized() override;
	UFUNCTION()
	void Login();
	float Percentage=0.0f;
	UFUNCTION()
	void Loading();
	UFUNCTION(BlueprintImplementableEvent, Category=UI)
	void LoadGame(const FText& PlayerName);
};
