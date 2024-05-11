// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LestaCharacter.h"
#include "GameFramework/GameModeBase.h"
#include "LestaGameMode.generated.h"

/** Base Game Mode class for the Lesta Start project. */
UCLASS()
class LESTASTART_API ALestaGameMode : public AGameModeBase
{
	GENERATED_BODY()

	virtual void PostLogin(APlayerController* NewPlayer) override;

	//void ClientDead(APawn* CharPawn);

	TArray<ALestaCharacter*> PlayerCharacters;
	int AlivePlayerCount = 0;

	// You can extend this class if required
	// Blueprint GameMode class is derived from the ALestaGameMode


};
