// HK9_GameModeBase.cpp


#include "GameModeBase/HK9_GameModeBase.h"
#include "PlayerController/HK9_PlayerController.h"
#include "PlayerState/HK9_PlayerState.h"
#include "GameStateBase/HK9_GameStateBase.h"

#include "Net/UnrealNetwork.h"

void AHK9_GameModeBase::BeginPlay()
{
	Super::BeginPlay();

	GenerateRandomNumbers();
}

void AHK9_GameModeBase::GenerateRandomNumbers()
{
	for (int i = 0; i < 3; ++i)
	{
		int NewNum = FMath::RandRange(1, 9);

		while (AnswerNumbers.Contains(NewNum))
		{
			NewNum = FMath::RandRange(1, 9);
		}

		AnswerNumbers.Add(NewNum);
	}
	UE_LOG(LogTemp, Warning, TEXT("Answer: %d%d%d"), AnswerNumbers[0], AnswerNumbers[1], AnswerNumbers[2])
}

FString AHK9_GameModeBase::CheckAnswer(const FString& InString, APlayerController* PC)
{
	TArray<int> NumArray = ConvertStringToIntArray(InString);

	int32 Strike = 0;
	int32 Ball = 0;

	for (int i = 0; i < 3; ++i)
	{
		if (AnswerNumbers[i] == NumArray[i])
		{
			++Strike;
		}
		else if (NumArray.Contains(AnswerNumbers[i]))
		{
			++Ball;
		}
	}

	if (Strike <= 0 && Ball <= 0)
	{
		return FString::Printf(TEXT("OUT"));
	}

	return FString::Printf(TEXT("%dS%dB"), Strike, Ball);
}

TArray<int> AHK9_GameModeBase::ConvertStringToIntArray(const FString& InString)
{
	TArray<int> NumArray;

	for (int i = 0; i < InString.Len(); ++i)
	{
		NumArray.Add(InString[i] - '0');
	}

	return NumArray;
}

void AHK9_GameModeBase::CheckGameResult(int32 Strike, APlayerController* PC)
{
	if (IsValid(PC))
	{
		AHK9_PlayerController* HK9_PC = Cast<AHK9_PlayerController>(PC);
		if (IsValid(HK9_PC))
		{
			if (Strike == 3)
			{
				AHK9_GameStateBase* GSB = GetWorld()->GetGameState<AHK9_GameStateBase>();
				if (IsValid(GSB))
				{
					FString WinnerText = FString::Printf(TEXT("Winner: %s"), *PC->GetPlayerState<AHK9_PlayerState>()->GetPlayerName());
					GSB->GameOverCallWidget(WinnerText);
				}
			}

			bool bNotAttempt = true;

			for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
			{
				APlayerController* PC = It->Get();
				if (IsValid(PC))
				{
					AHK9_PlayerState* PS = PC->GetPlayerState<AHK9_PlayerState>();
					if (IsValid(PS))
					{
						if (PS->GetCurrentAttempts() != PS->GetMaxAttempts())
						{
							bNotAttempt = false;
						}
					}
				}
			}
			
			if (bNotAttempt == true)
			{
				AHK9_GameStateBase* GSB = GetWorld()->GetGameState<AHK9_GameStateBase>();
				if (IsValid(GSB))
				{
					const FString& GameOverText = TEXT("Draw");
					GSB->GameOverCallWidget(GameOverText);
				}
			}
		}
	}
}

bool AHK9_GameModeBase::ChackClientNum(const FString InChatMessageString, APlayerController* PC)
{
	AHK9_PlayerController* HK9_PC = Cast<AHK9_PlayerController>(PC);

	UE_LOG(LogTemp, Warning, TEXT("Input: %s, Len: %d"), *InChatMessageString, InChatMessageString.Len());
	if (InChatMessageString.Len() == 3)
	{
		for (int i = 0; i < InChatMessageString.Len(); ++i)
		{
			if (!FChar::IsDigit(InChatMessageString[i]))
			{
				if (IsValid(HK9_PC))
				{
					HK9_PC->CheckFaliedMessage();
				}
				return false;
			}
		}

		TArray<int> NumArray = ConvertStringToIntArray(InChatMessageString);

		for (int i = 0; i < NumArray.Num(); ++i)
		{
			for (int j = i + 1; j < NumArray.Num(); ++j)
			{
				if (NumArray[i] == NumArray[j])
				{
					if (IsValid(HK9_PC))
					{
						HK9_PC->CheckFaliedMessage();
					}
					return false;
				}
			}
		}
	}
	else
	{
		if (IsValid(HK9_PC))
		{
			HK9_PC->CheckFaliedMessage();
		}
		return false;
	}
	return true;
}

bool AHK9_GameModeBase::IncrementPlayerAttempts(APlayerController* PC)
{
	bool bCanAttempt = true;
	UE_LOG(LogTemp, Warning, TEXT("bCanAttempt: %d"), bCanAttempt);
	if (IsValid(PC))
	{
		AHK9_PlayerState* PS = PC->GetPlayerState<AHK9_PlayerState>();
		if (IsValid(PS))
		{
			if (PS->GetCurrentAttempts() == PS->GetMaxAttempts())
			{
				bCanAttempt = false;
				UE_LOG(LogTemp, Warning, TEXT("CurrentAttempts: %d"), PS->GetCurrentAttempts());
				UE_LOG(LogTemp, Warning, TEXT("bCanAttempt: %d"), bCanAttempt);
			}

			if (bCanAttempt == true)
			{
				UE_LOG(LogTemp, Warning, TEXT("bCanAttempt: %d"), bCanAttempt);
				UE_LOG(LogTemp, Warning, TEXT("CurrentAttempts: %d"), PS->GetCurrentAttempts());
				PS->IncrementAttempts();
			}
		}
	}
	return bCanAttempt;
}