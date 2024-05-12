// Fill out your copyright notice in the Description page of Project Settings.

#include "Kismet/GameplayStatics.h"
#include "LestaGameMode.h"

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

//void ALestaGameMode::ClientDead(APawn* CharPawn)
//{
//	AlivePlayerCount--;
//	UE_LOG(LogTemp, Display, TEXT("EXECUTED"));
//	GEngine->AddOnScreenDebugMessage(-1, 4.f, FColor::Yellow, TEXT("MINUS FRIEND"));
//	if (AlivePlayerCount <= 0)
//	{
//		UGameplayStatics::OpenLevel(this, FName(UGameplayStatics::GetCurrentLevelName(this)));
//	}
//}