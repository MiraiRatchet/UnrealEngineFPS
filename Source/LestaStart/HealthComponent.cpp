// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	SetIsReplicated(true);

	MaximumHealth = 200;
	CurrentHealth = MaximumHealth;
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...

}

void UHealthComponent::FTakeDamage(float HealthPoints)
{
	CurrentHealth = FMath::Clamp(CurrentHealth - HealthPoints, 0, MaximumHealth);
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Green, FString::Printf(TEXT("%s health now %f"), *(GetOwner()->GetName()), CurrentHealth));
	OnHealthChangeEvent.ExecuteIfBound();
	if (CurrentHealth == 0)
	{
		FKill();
	}
}

void UHealthComponent::FHeal(float HealthPoints)
{
	CurrentHealth = FMath::Clamp(CurrentHealth + HealthPoints, 0, MaximumHealth);
	OnHealthChangeEvent.ExecuteIfBound();
}

void UHealthComponent::FKill() const
{
	if (OnDeadEvent.IsBound())
	{
		OnDeadEvent.Execute();
		return;
	}
		GetOwner()->Destroy();
}

int UHealthComponent::GetMaximumHealth() const
{
	return MaximumHealth;
}

float UHealthComponent::GetCurrentHealth() const
{
	return CurrentHealth;
}

float UHealthComponent::GetPercentHealth() const
{
	return CurrentHealth / MaximumHealth;
}

void UHealthComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UHealthComponent, MaximumHealth);
	DOREPLIFETIME(UHealthComponent, CurrentHealth);
}
