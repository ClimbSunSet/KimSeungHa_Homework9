// HK9_PlayerState.h

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "HK9_PlayerState.generated.h"

UCLASS()
class HOMEWORK9_API AHK9_PlayerState : public APlayerState
{
	GENERATED_BODY()
	
private:
	const int32 MaxAttempts = 3;

	UPROPERTY(Replicated)
	int32 CurrentAttempts = 0;

public:
	UFUNCTION(BlueprintCallable)
	int32 GetMaxAttempts() const;

	UFUNCTION(BlueprintCallable)
	int32 GetCurrentAttempts() const;

	void IncrementAttempts();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
