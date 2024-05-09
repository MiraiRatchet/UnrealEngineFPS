// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HealthComponent.h"
#include "GameFramework/Actor.h"
#include "Components/WidgetComponent.h"
#include "Engine/GameEngine.h"
#include "HealthHUD.h"
#include "CubeActor.generated.h"

UCLASS()
class LESTASTART_API ACubeActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACubeActor();

	UPROPERTY(Replicated, EditDefaultsOnly, BlueprintReadWrite)
	UWidgetComponent* WidgetComponent;


	UFUNCTION()
	void HealthBarChange();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

private:

	UPROPERTY(Replicated, EditDefaultsOnly)
	UHealthComponent* CubeHealth;

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* CubeMesh;

	UPROPERTY(Replicated, VisibleAnywhere)
	UHealthHUD* HealthHUD;
};
