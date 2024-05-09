// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthHUD.h"

void UHealthHUD::HealthUIChange(float CurrHealth, float MaxHealth, float PercentHealth)
{
	if (HealthProgressBar)
	{
		HealthProgressBar->SetPercent(PercentHealth);
	}
	if (HealthText)
	{
		HealthText->SetText(FText::FromString(FString::FromInt(FMath::CeilToInt(CurrHealth)) + "/" + FString::FromInt(MaxHealth)));
	}
}
