// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/GameEngine.h"
#include "GameFramework/Character.h"
#include "Net/UnrealNetwork.h"
#include "HealthComponent.generated.h"


UDELEGATE()
DECLARE_DYNAMIC_DELEGATE(FOnHealthChangeDelegate);

UDELEGATE()
DECLARE_DYNAMIC_DELEGATE(FOnDeadDelegate);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LESTASTART_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();

	FOnHealthChangeDelegate OnHealthChangeEvent;
	FOnDeadDelegate OnDeadEvent;

	UFUNCTION()
	void FTakeDamage(float HealthPoints);

	UFUNCTION()
	void FHeal(float HealthPoints);

	UFUNCTION()
	void FKill() const;

	UFUNCTION()
	int GetMaximumHealth() const;

	UFUNCTION()
	float GetCurrentHealth() const;

	UFUNCTION()
	float GetPercentHealth() const;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
private:
	UPROPERTY(Replicated, EditAnywhere, Category = "Health")
	int MaximumHealth;

	UPROPERTY(Replicated, VisibleAnywhere, Category = "Health")
	float CurrentHealth;
};
