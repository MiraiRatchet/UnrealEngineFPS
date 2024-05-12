// Fill out your copyright notice in the Description page of Project Settings.

#include "LestaPlayerController.h"
#include "Engine/World.h"
#include "EnhancedInputSubsystems.h"

void ALestaPlayerController::BeginPlay()
{
	Super::BeginPlay();
	if (const ULocalPlayer* LocalPlayer = Cast<ULocalPlayer>(Player))
	{
		if (auto* InputSystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			InputSystem->AddMappingContext(InputMapping, InputMappingPriority);
		}
	}
}


void ALestaPlayerController::ServerDealDamageToActor_Implementation(UHealthComponent* HP, float Damage)
{
	if (HasAuthority())
	{
		HP->SetCurrentHealth(FMath::Clamp(HP->GetCurrentHealth() - Damage, 0, HP->GetMaximumHealth()));
		HP->OnHealthChangeEvent.ExecuteIfBound();
	}
	//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Green, FString::Printf(TEXT("%s health now %f"), *(HP->GetName()), HP->GetCurrentHealth()));
	if (HasAuthority())
	{
		if (HP->GetCurrentHealth() == 0)
		{
			HP->FKill();
		}
	}
}

