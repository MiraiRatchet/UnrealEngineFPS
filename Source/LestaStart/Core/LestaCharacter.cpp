// Fill out your copyright notice in the Description page of Project Settings.

#include "LestaCharacter.h"
#include "EnhancedInputComponent.h"
#include "Camera/CameraComponent.h"

ALestaCharacter::ALestaCharacter()
{
	NetUpdateFrequency = 10.f;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("MainCamera"));
	CameraComponent->bUsePawnControlRotation = true; // Camera rotation is synchronized with Player Controller rotation
	CameraComponent->SetupAttachment(GetMesh());

	PlayerHealth = CreateDefaultSubobject<UHealthComponent>(TEXT("PlayerHealth"));
	LaserWeapon = CreateDefaultSubobject<ULaserComponent>(TEXT("LaserWeapon"));
	SphereWeapon = CreateDefaultSubobject<USphereWeaponComponent>(TEXT("SphereWeapon"));

	WeaponState = UWeaponState::SPHERE;
}

void ALestaCharacter::BeginPlay()
{
	Super::BeginPlay();
	PlayerHealth->OnDeadEvent.BindDynamic(this, &ALestaCharacter::PlayerDead);
}

void ALestaCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (EIC) // should validate component because developers can change input component class through Project Settings
	{
		EIC->BindAction(MoveInputAction, ETriggerEvent::Triggered, this, &ThisClass::OnMoveInput);
		EIC->BindAction(LookInputAction, ETriggerEvent::Triggered, this, &ThisClass::OnLookInput);
		EIC->BindAction(ShootInputAction, ETriggerEvent::Triggered, this, &ThisClass::OnShootTriggeredInput);
		EIC->BindAction(ShootInputAction, ETriggerEvent::Ongoing, this, &ThisClass::OnShootOngoingInput);
		EIC->BindAction(ChangeWeaponInputAction, ETriggerEvent::Triggered, this, &ThisClass::OnWeaponChangeInput);
	}
	else
	{
		// Print error message into log
		// You can read more here: https://dev.epicgames.com/documentation/en-us/unreal-engine/logging-in-unreal-engine
		UE_LOG(LogInput, Error, TEXT("Unexpected input component class: %s"), *GetFullNameSafe(PlayerInputComponent))
	}

}

void ALestaCharacter::OnMoveInput(const FInputActionInstance& InputActionInstance)
{
	// Controller rotation Yaw determines which direction Character is facing
	// so MoveForward = along that direction AND MoveRight = to the right of that direction

	const float YawDegree = GetControlRotation().Yaw; // controller rotation Yaw (in degrees)
	const float YawRadian = FMath::DegreesToRadians(YawDegree); // controller rotation Yaw (in radians)
	const FVector ForwardDirection = FVector(FMath::Cos(YawRadian), FMath::Sin(YawRadian), 0.f);
	const FVector RightDirection = FVector(FMath::Cos(YawRadian + UE_HALF_PI), FMath::Sin(YawRadian + UE_HALF_PI), 0.f);

	const FVector2D Input2D = InputActionInstance.GetValue().Get<FVector2D>();
	AddMovementInput(ForwardDirection * Input2D.X + RightDirection * Input2D.Y);
}

void ALestaCharacter::OnLookInput(const FInputActionInstance& InputActionInstance)
{
	const FVector2D Input2D = InputActionInstance.GetValue().Get<FVector2D>();
	AddControllerYawInput(Input2D.X);
	AddControllerPitchInput(Input2D.Y);
}

void ALestaCharacter::OnShootTriggeredInput(const FInputActionInstance& InputActionInstance)
{
	switch (WeaponState) {
	case (UWeaponState::SPHERE):
		SphereWeapon->ChargedShot(GetActorLocation());
		break;
	}
	IsCharging = false;
}

void ALestaCharacter::OnShootOngoingInput(const FInputActionInstance& InputActionInstance)
{
	IsCharging = true;
	switch (WeaponState) {
	case (UWeaponState::LASER):
		if (PistolMuzzle)
		{
			LaserWeapon->ChargedShot(PistolMuzzle->GetComponentLocation(), CameraComponent->GetComponentLocation(), CameraComponent->GetComponentLocation() + CameraComponent->GetForwardVector() * LaserWeapon->GetMaxHitDistance(), ECC_Visibility);
		}
		break;
	case (UWeaponState::SPHERE):
		SphereWeapon->ChargingDrawRadius(GetActorLocation(), InputActionInstance.GetElapsedTime());
		break;
	}
}

void ALestaCharacter::OnWeaponChangeInput(const FInputActionInstance& InputActionInstance)
{
	if (IsCharging)
	{
		return;
	}

	auto KeyPressed = FMath::FloorToInt(InputActionInstance.GetValue().Get<float>());
	if (KeyPressed == 2)
	{
		WeaponState = UWeaponState::SPHERE;
		GEngine->AddOnScreenDebugMessage(-1, 4.0f, FColor::Black, "SPHERE");
		return;
	}
	if (KeyPressed == 3)
	{
		WeaponState = UWeaponState::LASER;
		GEngine->AddOnScreenDebugMessage(-1, 4.0f, FColor::Black, "LASER");
		return;
	}
	switch (WeaponState) {
	case (UWeaponState::LASER):
		WeaponState = UWeaponState::SPHERE;
		GEngine->AddOnScreenDebugMessage(-1, 4.0f, FColor::Black, "SPHERE");
		break;
	case (UWeaponState::SPHERE):
		WeaponState = UWeaponState::LASER;
		GEngine->AddOnScreenDebugMessage(-1, 4.0f, FColor::Black, "LASER");
		break;
	}
}


void ALestaCharacter::PlayerDead()
{
	auto PlayerController = Cast<APlayerController>(GetController());
	if (PlayerController)
	{
		//PlayerController->UnPossess();
		if (OnClientUnpossess.IsBound())
		{
			UE_LOG(LogTemp, Display, TEXT("ISBOUND"));
			OnClientUnpossess.Execute(PlayerController);
		}
	}
	//UGameplayStatics::OpenLevel(this, FName(UGameplayStatics::GetCurrentLevelName(this)));
}