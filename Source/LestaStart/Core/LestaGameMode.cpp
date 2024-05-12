// Fill out your copyright notice in the Description page of Project Settings.

#include "LestaGameMode.h"
#include "Kismet/GameplayStatics.h"

void ALestaGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
	if (NewPlayer)
	{
		auto PlayerChar = Cast<ALestaCharacter>(NewPlayer->GetPawn());
		PlayerCharacters.AddUnique(PlayerChar);
		PlayerChar->OnClientUnpossess.BindLambda([this](APlayerController* PControl){
			AlivePlayerCount--;
			auto Pawn = PControl->GetPawn();
			if (AlivePlayerCount <= 0)
			{
				GetWorld()->ServerTravel("/Game/Maps/LestaStartMap");
			}
			PControl->UnPossess();
			Pawn->Destroy();
			});
		AlivePlayerCount++;
		GEngine->AddOnScreenDebugMessage(-1, 4.f, FColor::Yellow, TEXT("NEW FRIEND"));
	}
}
