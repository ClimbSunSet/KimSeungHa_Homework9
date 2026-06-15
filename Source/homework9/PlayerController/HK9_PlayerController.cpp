// HK9_PlayerController.cpp


#include "PlayerController/HK9_PlayerController.h"
#include "GameModeBase/HK9_GameModeBase.h"
#include "UI/HK9_ChatInput.h"
#include "UI/HK9_GameOverWidget.h"

#include "GameFramework/GameMode.h"

#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"

void AHK9_PlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (IsLocalController())
	{
		FInputModeUIOnly InputModeUIOnly;
		SetInputMode(InputModeUIOnly);

		if (IsValid(ChatInputWidgetClass))
		{
			ChatInputWidgetInstance = CreateWidget<UHK9_ChatInput>(this, ChatInputWidgetClass);
			if (IsValid(ChatInputWidgetInstance))
			{
				ChatInputWidgetInstance->AddToViewport();
			}
		}
	}
}

void AHK9_PlayerController::SetChatMessageSrting_Implementation(const FString& InChatMessageString)
{
	AGameModeBase* OwningGameModeBase = GetWorld()->GetAuthGameMode();
	if (IsValid(OwningGameModeBase))
	{
		AHK9_GameModeBase* GMB = Cast<AHK9_GameModeBase>(OwningGameModeBase);

		if (IsValid(GMB))
		{
			if (GMB->ChackClientNum(InChatMessageString, this))
			{
				if (GMB->IncrementPlayerAttempts(this))
				{
					FString Result = GMB->CheckAnswer(InChatMessageString, this);

					if (Result[0] == 'O')
					{
						FString Out = TEXT("OUT");
						GMB->CheckGameResult(0, this);
						PrintChatMessageString(Out);
						return;
					}

					GMB->CheckGameResult(Result[0] - '0', this);
					PrintChatMessageString(Result);
				}
				else
				{
					InputCountConsumedMessage();
				}
			}
		}
	}
}

void AHK9_PlayerController::PrintChatMessageString_Implementation(const FString& InChatMessageString)
{
	UE_LOG(LogTemp, Warning, TEXT("PrintChat: %s"), *InChatMessageString);
	if (IsLocalController())
	{
		UKismetSystemLibrary::PrintString(this, InChatMessageString, true, false, FLinearColor::Blue, 5.0f);
	}
}

void AHK9_PlayerController::CheckFaliedMessage_Implementation()
{
	if (!HasAuthority())
	{
		ChatMessageString = TEXT("다시 입력하세요");
		
		UKismetSystemLibrary::PrintString(this, ChatMessageString, true, false, FLinearColor::Blue, 5.0f);
	}
}

void AHK9_PlayerController::InputCountConsumedMessage_Implementation()
{
	FString InputCountConsumedMessage = TEXT("입력 횟수를 모두 소모했습니다");

	UKismetSystemLibrary::PrintString(this, InputCountConsumedMessage, true, false, FLinearColor::Green, 5.0f);
}

void AHK9_PlayerController::CallGameOverWidget(const FString& GameOverText)
{
	if (IsLocalController())
	{
		if (IsValid(GameOverWidgetClass))
		{
			GameOverWidgetInstance = CreateWidget<UHK9_GameOverWidget>(this, GameOverWidgetClass);
			if (IsValid(GameOverWidgetInstance))
			{
				GameOverWidgetInstance->SetGameOverText(GameOverText);
				GameOverWidgetInstance->AddToViewport();
			}
		}
	}
}

void AHK9_PlayerController::RequestGameRestart_Implementation()
{
	UE_LOG(LogTemp, Warning, TEXT("Called RequestGameRestart"))
	AHK9_GameModeBase* GM = Cast<AHK9_GameModeBase>(GetWorld()->GetAuthGameMode());
	if (IsValid(GM))
	{
		UE_LOG(LogTemp, Warning, TEXT("Valid GM"))
		UGameplayStatics::OpenLevel(GetWorld(), FName(*GetWorld()->GetName()), true);
	}
}
