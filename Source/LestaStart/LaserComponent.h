// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HealthComponent.h"
#include "Engine/GameEngine.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/ActorComponent.h"
#include "LaserComponent.generated.h"



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LESTASTART_API ULaserComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	ULaserComponent();

	UFUNCTION()
	void ChargedShot(FVector DrawStart, FVector TraceStart, FVector TraceEnd, ECollisionChannel Channel);

	UFUNCTION()
	float GetMaxHitDistance() const;

	UFUNCTION()
	FVector GetTraceEnd() const;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	FCollisionQueryParams CollisionParams;

	UPROPERTY(VisibleAnywhere)
	bool IsCharging = false;

	UPROPERTY(EditAnywhere)
	int DamagePerSecond = 15;

	UPROPERTY(EditAnywhere)
	float MaxHitDistance = 300;

	UPROPERTY(VisibleInstanceOnly)
	FVector TraceEndLoc;
};
