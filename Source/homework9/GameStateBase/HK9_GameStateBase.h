// HK9_GameStateBase.h

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "HK9_GameStateBase.generated.h"

UCLASS()
class HOMEWORK9_API AHK9_GameStateBase : public AGameStateBase
{
	GENERATED_BODY()
	
public:
	UFUNCTION(NetMulticast, Reliable)
	void GameOverCallWidget(const FString& GameOverText);
};
