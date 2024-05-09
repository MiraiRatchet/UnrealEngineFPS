// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputAction.h"
#include "../HealthComponent.h"
#include "../LaserComponent.h"
#include "../SphereWeaponComponent.h"
//#include "Components/Widget.h"
#include "LestaCharacter.generated.h"

class UCameraComponent;

UENUM(BlueprintType)
enum class UWeaponState : uint8
{
	LASER,
	SPHERE,
};

/** Base Character class for the Lesta Start project. */
UCLASS()
class LESTASTART_API ALestaCharacter : public ACharacter
{
	GENERATED_BODY()

	// You can extend this class if required
	// Blueprint Character class is derived from the ALestaCharacter

public:
	ALestaCharacter();
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneComponent* PistolMuzzle = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UHealthComponent* PlayerHealth;

private:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UCameraComponent> CameraComponent;

	/** Input action assigned to movement. */
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> MoveInputAction;

	/** Input action assigned to camera movement. */
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> LookInputAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> ShootInputAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input") 
	TObjectPtr<UInputAction> ChangeWeaponInputAction;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	ULaserComponent* LaserWeapon;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	USphereWeaponComponent* SphereWeapon;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	UWeaponState WeaponState;

	UPROPERTY()
	bool IsCharging = false;
protected:

	virtual void OnMoveInput(const FInputActionInstance& InputActionInstance);
	virtual void OnLookInput(const FInputActionInstance& InputActionInstance);
	virtual void OnShootTriggeredInput(const FInputActionInstance& InputActionInstance);
	virtual void OnShootOngoingInput(const FInputActionInstance& InputActionInstance);
	virtual void OnWeaponChangeInput(const FInputActionInstance& InputActionInstance);

	UFUNCTION()
	void PlayerDead();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
};
