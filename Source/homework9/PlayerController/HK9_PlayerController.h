// HK9_PlayerController.h

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "HK9_PlayerController.generated.h"

class UHK9_ChatInput;
class UHK9_GameOverWidget;

UCLASS()
class HOMEWORK9_API AHK9_PlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;

	UFUNCTION(Server, Reliable)
	void SetChatMessageSrting(const FString& InChatMessageString);
	
	UFUNCTION(Client, Reliable)
	void PrintChatMessageString(const FString& InChatMessageString);

	UFUNCTION(Client, Reliable)
	void CheckFaliedMessage();

	UFUNCTION()
	void CallGameOverWidget(const FString& GameOverText);

	UFUNCTION(Server, Reliable)
	void RequestGameRestart();

protected:
	UPROPERTY(EditDefaultsOnly, Category = "ChatWidget")
	TSubclassOf<UHK9_ChatInput> ChatInputWidgetClass;

	UPROPERTY()
	TObjectPtr<UHK9_ChatInput> ChatInputWidgetInstance;

	FString ChatMessageString;

	UPROPERTY(EditDefaultsOnly, Category = "GameOverWidget")
	TSubclassOf<UHK9_GameOverWidget> GameOverWidgetClass;

	UPROPERTY()
	TObjectPtr<UHK9_GameOverWidget> GameOverWidgetInstance;
};
