// HK9_GameOverWidget.h

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HK9_GameOverWidget.generated.h"

class UButton;

UCLASS()
class HOMEWORK9_API UHK9_GameOverWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;

	virtual void NativeDestruct() override;

private:
	UPROPERTY()
	FString GameOverText;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> ReStartButton;

public:
	UFUNCTION(BlueprintCallable)
	FString GetGameOverText() const;

	UFUNCTION(BlueprintCallable)
	void SetGameOverText(FString NewGameOverText);

protected:
	UFUNCTION(BlueprintCallable)
	void OnRestartButtonClicked();
};
