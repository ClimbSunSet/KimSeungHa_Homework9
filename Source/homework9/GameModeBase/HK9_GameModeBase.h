// HK9_GameModeBase.h

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "HK9_GameModeBase.generated.h"

class AHK9_PlayerController;

UCLASS()
class HOMEWORK9_API AHK9_GameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	TArray<int> AnswerNumbers;

private:
	UFUNCTION()
	void GenerateRandomNumbers();

public:
	UFUNCTION()
	FString CheckAnswer(const FString& InString, APlayerController* PC);

private:
	UFUNCTION()
	TArray<int> ConvertStringToIntArray(const FString& InString);

public:
	void CheckGameResult(int32 Strike,APlayerController* PC);

public:
	bool ChackClientNum(const FString InChatMessageString, APlayerController* PC);

	bool IncrementPlayerAttempts(APlayerController* PC);
};
