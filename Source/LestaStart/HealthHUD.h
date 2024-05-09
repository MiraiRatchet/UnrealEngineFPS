// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"
#include "HealthHUD.generated.h"

/**
 * 
 */
UCLASS()
class LESTASTART_API UHealthHUD : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION()
	void HealthUIChange(float CurrHealth, float MaxHealth, float PercentHealth);

private:
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UProgressBar* HealthProgressBar;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UTextBlock* HealthText;
	
};
