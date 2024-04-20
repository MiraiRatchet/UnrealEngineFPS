// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/GameEngine.h"
#include "Kismet/KismetSystemLibrary.h"
#include "HealthComponent.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SphereWeaponComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LESTASTART_API USphereWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USphereWeaponComponent();

	UPROPERTY(EditDefaultsOnly)
	int UnchargedDamage = 15;

	UPROPERTY(EditDefaultsOnly)
	int DamagePerSecond = 20;

	UPROPERTY(EditDefaultsOnly)
	int MaxChargedDamage = 110;

	UPROPERTY(EditDefaultsOnly)
	float DamageRadius = 300;

	UPROPERTY(VisibleAnywhere)
	float CurrentChargedDamage = 0;

	UFUNCTION()
	void ChargedShot(FVector DrawingLocation);

	UFUNCTION()
	void ChargingDrawRadius(FVector DrawingLocation, double ElapsedTime);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;


public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
