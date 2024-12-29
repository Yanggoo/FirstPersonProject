// Fill out your copyright notice in the Description page of Project Settings.


#include "LoginUserWidget.h"

#include "Components/Button.h"
#include "Components/EditableText.h"
#include "Components/ProgressBar.h"
#include "FirstPersonGameInstance.h"

void ULoginUserWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	ProgressBar->SetVisibility(ESlateVisibility::Hidden);
	Button_Login->OnPressed.AddDynamic(this,&ULoginUserWidget::Login);
}

void ULoginUserWidget::Login()
{
	Name = EditableText_Name->GetText();
	FText PassWord = EditableText_PassWord->GetText();
	ProgressBar->SetVisibility(ESlateVisibility::Visible);
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ULoginUserWidget::Loading, 0.2f, true);
	if(UFirstPersonGameInstance* GameInstance = Cast<UFirstPersonGameInstance>(GetGameInstance()))
	{
		GameInstance->SetPlayerName(Name.ToString());
	}
}

void ULoginUserWidget::Loading()
{
	Percentage+=0.1f;
	if(Percentage>1.0f)
	{
		Percentage=1.0f;
		GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
		LoadGame(Name);
	}
	ProgressBar->SetPercent(Percentage);
}

