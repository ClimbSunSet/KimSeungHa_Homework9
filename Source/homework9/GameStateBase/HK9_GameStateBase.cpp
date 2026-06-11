// HK9_GameStateBase.cpp


#include "GameStateBase/HK9_GameStateBase.h"
#include "PlayerController/HK9_PlayerController.h"

void AHK9_GameStateBase::GameOverCallWidget_Implementation(const FString& GameOverText)
{
	if (!HasAuthority())
	{
		AHK9_PlayerController* PC = GetWorld()->GetFirstPlayerController<AHK9_PlayerController>();
		if (IsValid(PC))
		{
			PC->CallGameOverWidget(GameOverText);
		}
	}
}
