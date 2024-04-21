// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/GameEngine.h"
#include "HealthComponent.h"
#include "LaserComponent.h"
#include "Components/SphereComponent.h"
#include "TurretLaserActor.generated.h"

UCLASS()
class LESTASTART_API ATurretLaserActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATurretLaserActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly)
	USceneComponent* TraceStartPosition;

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* TurretMesh;

	UPROPERTY(EditAnywhere)
	USphereComponent* SphereCollision;

	UPROPERTY(EditDefaultsOnly)
	UHealthComponent* TurretHealth;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	ULaserComponent* LaserWeapon;

	UPROPERTY(VisibleAnywhere)
	AActor* OverlappingActor = nullptr;

	UFUNCTION()
	void OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnSphereEndOverlap(UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	FVector TraceStart;

};
