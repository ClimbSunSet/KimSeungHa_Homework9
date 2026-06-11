// HK9_ChatInput.cpp


#include "UI/HK9_ChatInput.h"

#include "Components/EditableTextBox.h"
#include "PlayerController/HK9_PlayerController.h"

void UHK9_ChatInput::NativeConstruct()
{
	Super::NativeConstruct();
	
	if (!EditableTextBox_ChatInput)
	{
		return;
	}

	if (EditableTextBox_ChatInput->OnTextCommitted.IsAlreadyBound(this, &ThisClass::OnChatInputTextCommitted) == false)
	{
		EditableTextBox_ChatInput->OnTextCommitted.AddDynamic(this, &ThisClass::OnChatInputTextCommitted);
	}
}

void UHK9_ChatInput::NativeDestruct()
{
	Super::NativeDestruct();

	if (!EditableTextBox_ChatInput) 
	{
		return;
	}

	if (EditableTextBox_ChatInput->OnTextCommitted.IsAlreadyBound(this, &ThisClass::OnChatInputTextCommitted) == true)
	{
		EditableTextBox_ChatInput->OnTextCommitted.RemoveDynamic(this, &ThisClass::OnChatInputTextCommitted);
	}
}

void UHK9_ChatInput::OnChatInputTextCommitted(const FText& Text, ETextCommit::Type CommitMethod)
{
	if (CommitMethod == ETextCommit::OnEnter)
	{
		APlayerController* OwningPlayerController = GetOwningPlayer();
		if (IsValid(OwningPlayerController) == true)
		{
			AHK9_PlayerController* OwningHK9_PlayerController = Cast<AHK9_PlayerController>(OwningPlayerController);
			if (IsValid(OwningHK9_PlayerController) == true)
			{
				OwningHK9_PlayerController->SetChatMessageSrting(Text.ToString());

				EditableTextBox_ChatInput->SetText(FText());
			}
		}
	}
}
