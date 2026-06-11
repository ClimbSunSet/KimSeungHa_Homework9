// HK9_GameOverWidget.cpp


#include "UI/HK9_GameOverWidget.h"
#include "PlayerController/HK9_PlayerController.h"

#include "Components/Button.h"

void UHK9_GameOverWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (!ReStartButton)
	{
		return;
	}

	if (ReStartButton->OnClicked.IsAlreadyBound(this, &ThisClass::OnRestartButtonClicked) == false)
	{
		ReStartButton->OnClicked.AddDynamic(this, &ThisClass::OnRestartButtonClicked);
	}
}

void UHK9_GameOverWidget::NativeDestruct()
{
	Super::NativeDestruct();

	if (!ReStartButton)
	{
		return;
	}

	if (ReStartButton->OnClicked.IsAlreadyBound(this, &ThisClass::OnRestartButtonClicked) == true)
	{
		ReStartButton->OnClicked.RemoveDynamic(this, &ThisClass::OnRestartButtonClicked);
	}
}

FString UHK9_GameOverWidget::GetGameOverText() const
{
	return GameOverText;
}

void UHK9_GameOverWidget::SetGameOverText(FString NewGameOverText)
{
	GameOverText = NewGameOverText;
}

void UHK9_GameOverWidget::OnRestartButtonClicked()
{
	APlayerController* PC = GetOwningPlayer();
	UE_LOG(LogTemp, Warning, TEXT("Called OnRestartButtonClicked"))
	if (IsValid(PC))
	{
		AHK9_PlayerController* HK9_PC = Cast<AHK9_PlayerController>(PC);
		if (IsValid(HK9_PC))
		{
			UE_LOG(LogTemp, Warning, TEXT("Valid HK9_PC"))
			HK9_PC->RequestGameRestart();
		}
	}
}
