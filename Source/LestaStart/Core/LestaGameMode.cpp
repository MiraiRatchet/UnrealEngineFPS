// Fill out your copyright notice in the Description page of Project Settings.


#include "LestaGameMode.h"

void ALestaGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
	if (NewPlayer)
	{
		auto PlayerChar = Cast<ALestaCharacter>(NewPlayer->GetPawn());
		PlayerCharacters.AddUnique(PlayerChar);
		AlivePlayerCount++;
		GEngine->AddOnScreenDebugMessage(-1, 4.f, FColor::Yellow, TEXT("NEW FRIEND"));
	}
}