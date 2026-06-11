// HK9_PlayerState.cpp


#include "PlayerState/HK9_PlayerState.h"

#include "Net/UnrealNetwork.h"

int32 AHK9_PlayerState::GetMaxAttempts() const
{
	return MaxAttempts;
}

int32 AHK9_PlayerState::GetCurrentAttempts() const
{
	return CurrentAttempts;
}

void AHK9_PlayerState::IncrementAttempts()
{
	++CurrentAttempts;
}

void AHK9_PlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AHK9_PlayerState, CurrentAttempts);
}
