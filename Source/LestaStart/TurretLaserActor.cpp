// Fill out your copyright notice in the Description page of Project Settings.


#include "TurretLaserActor.h"
#include "Math/UnrealMathUtility.h"
#include "Net/UnrealNetwork.h"

// Sets default values
ATurretLaserActor::ATurretLaserActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CubeMesh"));
	SetRootComponent(TurretMesh);

	CylinderMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CylinderMesh"));
	CylinderMesh->SetupAttachment(GetRootComponent());

	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereTrigger"));
	SphereCollision->SetSphereRadius(200);
	SphereCollision->SetGenerateOverlapEvents(true);
	SphereCollision->SetupAttachment(GetRootComponent());

	TraceStartPosition = CreateDefaultSubobject<USceneComponent>(TEXT("TraceStartPosition"));
	TraceStartPosition->SetupAttachment(GetRootComponent());

	TurretHealth = CreateDefaultSubobject<UHealthComponent>(TEXT("TurretHealth"));
	LaserWeapon = CreateDefaultSubobject<ULaserComponent>(TEXT("LaserWeapon"));

	CylinderMesh->SetRelativeLocation(FVector(0, 0, 75));
}

// Called when the game starts or when spawned
void ATurretLaserActor::BeginPlay()
{
	Super::BeginPlay();

	TraceStart = TraceStartPosition->GetComponentLocation();

	SphereCollision->OnComponentBeginOverlap.AddDynamic(this, &ATurretLaserActor::OnSphereBeginOverlap);
	SphereCollision->OnComponentEndOverlap.AddDynamic(this, &ATurretLaserActor::OnSphereEndOverlap);

	if (TurretHealth)
	TurretHealth->OnHealthChangeEvent.BindDynamic(this, &ATurretLaserActor::HealthBarChange);
	HealthHUD = Cast<UHealthHUD>(HealthWidget->GetUserWidgetObject());
	HealthBarChange();

	CylinderWorldLocation = CylinderMesh->GetComponentLocation();
	PastRotationZ = CylinderMesh->GetComponentRotation().Yaw;
}
// Called every frame
void ATurretLaserActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (OverlappingActor)
	{
		RotateToPlayer(DeltaTime);
		if (LaserWeapon && FMath::IsNearlyEqual(CylinderMesh->GetComponentRotation().Yaw, NeededRotatorYaw, 5.0))
		{
			LaserWeapon->ChargedShot(TraceStart, TraceStart, OverlappingActor->GetActorLocation(), ECC_Pawn);
		}
	}

}

void ATurretLaserActor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ATurretLaserActor, TurretHealth);
	DOREPLIFETIME(ATurretLaserActor, CylinderMesh);
	DOREPLIFETIME(ATurretLaserActor, HealthWidget);
	DOREPLIFETIME(ATurretLaserActor, HealthHUD);
	DOREPLIFETIME(ATurretLaserActor, OverlappingActor);

}

void ATurretLaserActor::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OverlappingActor)
	{
		OverlappingActor = OtherActor;
	}
}

void ATurretLaserActor::OnSphereEndOverlap(UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor == OverlappingActor)
	{
		OverlappingActor = nullptr;
	}
}


void ATurretLaserActor::HealthBarChange()
{
	if (HealthHUD && TurretHealth)
	{
		HealthHUD->HealthUIChange(TurretHealth->GetCurrentHealth(), TurretHealth->GetMaximumHealth(), TurretHealth->GetPercentHealth());
	}
}

void ATurretLaserActor::RotateToPlayer(float DeltaTime)
{
	NeededRotatorYaw = UKismetMathLibrary::FindLookAtRotation(CylinderWorldLocation, OverlappingActor->GetActorLocation()).Yaw + 90;
	float Remainder = 0;
	UKismetMathLibrary::FMod(NeededRotatorYaw - PastRotationZ, 360.0f, Remainder);
	float NewYaw = PastRotationZ + Remainder * DeltaTime * RotationSpeed;
	if (CylinderMesh)
	CylinderMesh->SetWorldRotation(FRotator(CylinderMesh->GetComponentRotation().Pitch, NewYaw, CylinderMesh->GetComponentRotation().Roll));
	PastRotationZ = NewYaw;
}