// Fill out your copyright notice in the Description page of Project Settings.


#include "LaserComponent.h"

// Sets default values for this component's properties
ULaserComponent::ULaserComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void ULaserComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void ULaserComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void ULaserComponent::ChargedShot(FVector DrawStart, FVector TraceStart, FVector TraceEnd, ECollisionChannel Channel)
{
	double DeltaTime = GetWorld()->GetDeltaSeconds();
	FHitResult Hit;
	DrawDebugLine(GetWorld(), DrawStart, TraceEnd, FColor::Magenta);
	bool bBlockHit = GetWorld()->LineTraceSingleByChannel(Hit, DrawStart, TraceEnd, Channel);
	if (bBlockHit)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 4.0f, FColor::Green, Hit.GetActor()->GetName());
		auto HitHealth = Hit.GetActor()->FindComponentByClass<UHealthComponent>();
		if (HitHealth)
		{
			HitHealth->FTakeDamage(DeltaTime * DamagePerSecond);
		}
	}
}

