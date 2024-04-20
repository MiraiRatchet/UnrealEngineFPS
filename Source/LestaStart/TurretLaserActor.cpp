// Fill out your copyright notice in the Description page of Project Settings.


#include "TurretLaserActor.h"

// Sets default values
ATurretLaserActor::ATurretLaserActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CubeMesh"));
	SetRootComponent(TurretMesh);

	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereTrigger"));
	SphereCollision->SetSphereRadius(200);
	SphereCollision->SetGenerateOverlapEvents(true);
	SphereCollision->SetupAttachment(GetRootComponent());

	TraceStartPosition = CreateDefaultSubobject<USceneComponent>(TEXT("TraceStartPosition"));
	TraceStartPosition->SetupAttachment(GetRootComponent());

	TurretHealth = CreateDefaultSubobject<UHealthComponent>(TEXT("TurretHealth"));
	LaserWeapon = CreateDefaultSubobject<ULaserComponent>(TEXT("LaserWeapon"));

}

// Called when the game starts or when spawned
void ATurretLaserActor::BeginPlay()
{
	Super::BeginPlay();

	SphereCollision->OnComponentBeginOverlap.AddDynamic(this, &ATurretLaserActor::OnSphereBeginOverlap);
	SphereCollision->OnComponentEndOverlap.AddDynamic(this, &ATurretLaserActor::OnSphereEndOverlap);
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Cyan, SphereCollision->OnComponentBeginOverlap.IsBound()? "true" : "false");
}

// Called every frame
void ATurretLaserActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATurretLaserActor::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Cyan, "OVERLAPPPPPPPPPP");
	if (!OverlappingActor)
	{
		OverlappingActor = OtherActor;
	}
}

void ATurretLaserActor::OnSphereEndOverlap(UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Cyan, "OVERLAPPPPPPPPPP EEEEEEEND");
	if (OtherActor == OverlappingActor)
	{
		OverlappingActor = nullptr;
	}
}

