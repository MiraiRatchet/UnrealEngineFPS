// Fill out your copyright notice in the Description page of Project Settings.


#include "CubeActor.h"
#include "Net/UnrealNetwork.h"

// Sets default values
ACubeActor::ACubeActor()
{
	bReplicates = true;
	PrimaryActorTick.bCanEverTick = true;

	CubeHealth = CreateDefaultSubobject<UHealthComponent>(TEXT("CubeHealth"));
	CubeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CubeMesh"));
	SetRootComponent(CubeMesh);
}

// Called when the game starts or when spawned
void ACubeActor::BeginPlay()
{
	Super::BeginPlay();
	if (CubeHealth)
	CubeHealth->OnHealthChangeEvent.BindDynamic(this, &ACubeActor::HealthBarChange);
	if (WidgetComponent)
	HealthHUD = Cast<UHealthHUD>(WidgetComponent->GetUserWidgetObject());
	HealthBarChange();
}

// Called every frame
void ACubeActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACubeActor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ACubeActor, CubeHealth);
	DOREPLIFETIME(ACubeActor, HealthHUD);
	DOREPLIFETIME(ACubeActor, WidgetComponent);
}

void ACubeActor::HealthBarChange()
{
	if (HealthHUD && CubeHealth)
	{
		HealthHUD->HealthUIChange(CubeHealth->GetCurrentHealth(), CubeHealth->GetMaximumHealth(), CubeHealth->GetPercentHealth());
	}
}

