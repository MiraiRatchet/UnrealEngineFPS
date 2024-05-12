// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/GameEngine.h"
#include "HealthComponent.h"
#include "LaserComponent.h"
#include "HealthHUD.h"
#include "Components/WidgetComponent.h"
#include "Components/SphereComponent.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Kismet/KismetMathLibrary.h"
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

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	UWidgetComponent* HealthWidget;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION()
	void OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnSphereEndOverlap(UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

private:
	FVector TraceStart;

	UFUNCTION()
	void HealthBarChange();

	FVector CylinderWorldLocation;

	float PastRotationZ;

	UPROPERTY(EditDefaultsOnly, meta = (ClampMin = "0", ClampMax = "1"))
	float RotationSpeed = 0.7;

	UFUNCTION()
	void RotateToPlayer(float DeltaTime);
	float NeededRotatorYaw = 0;

	UPROPERTY(Replicated, VisibleInstanceOnly)
	AActor* OverlappingActor = nullptr;

	UPROPERTY(Replicated, EditDefaultsOnly)
	UHealthComponent* TurretHealth;

	UPROPERTY(VisibleDefaultsOnly)
	UHealthHUD* HealthHUD;

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* TurretMesh;

	UPROPERTY(Replicated, EditDefaultsOnly)
	UStaticMeshComponent* CylinderMesh;

	UPROPERTY(EditAnywhere)
	USphereComponent* SphereCollision;

	UPROPERTY(Replicated, EditDefaultsOnly, Category = "Weapon")
	ULaserComponent* LaserWeapon;

	UPROPERTY(EditDefaultsOnly)
	USceneComponent* TraceStartPosition;

	UPROPERTY(Replicated, VisibleInstanceOnly)
	FVector TraceEnd;

	UPROPERTY(EditDefaultsOnly)
	UNiagaraComponent* NiagaraComponent;
};
