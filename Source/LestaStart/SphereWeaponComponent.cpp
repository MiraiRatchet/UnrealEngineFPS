
// Fill out your copyright notice in the Description page of Project Settings.

#include "SphereWeaponComponent.h"
#include"./Core/LestaPlayerController.h"

// Sets default values for this component's properties
USphereWeaponComponent::USphereWeaponComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USphereWeaponComponent::BeginPlay()
{
	Super::BeginPlay();
	CurrentChargedDamage = 0;

	// ...
	
}


// Called every frame
void USphereWeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void USphereWeaponComponent::ChargedShot(FVector DrawingLocation)
{
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, FString::Printf(TEXT("%f FIRED"), CurrentChargedDamage));
	TArray<FHitResult>Hits;
	bool bBlockHit = GetWorld()->SweepMultiByChannel(Hits, DrawingLocation, DrawingLocation, FRotator::ZeroRotator.Quaternion(), ECC_Visibility, FCollisionShape::MakeSphere(DamageRadius));
	if (bBlockHit)
	{
		for (auto &Hit : Hits)
		{
			auto HitHealth = Hit.GetActor()->FindComponentByClass<UHealthComponent>();
			if (HitHealth)
			{
				//auto PlayerController = Cast<ALestaPlayerController>(GetWorld()->GetFirstPlayerController());
				//if (PlayerController)
				//{
				//	PlayerController->DealDamageToActor(HitHealth, CurrentChargedDamage);
				//}
				HitHealth->FTakeDamage(CurrentChargedDamage);
			}
		}
	}
	CurrentChargedDamage = 0;
}

void USphereWeaponComponent::ChargingDrawRadius(FVector DrawingLocation, double ElapsedTime)
{
	DrawDebugSphere(GetWorld(), DrawingLocation, DamageRadius, 16, FColor::Blue);
	CurrentChargedDamage = FMath::Clamp(UnchargedDamage + DamagePerSecond * ElapsedTime, UnchargedDamage, MaxChargedDamage);
}

