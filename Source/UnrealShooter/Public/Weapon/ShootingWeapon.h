// Copyright Atennop and Krypton. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "WeaponType.h"
#include "Interfaces/IFirearm.h"
#include "GameFramework/Actor.h"
#include "ShootingWeapon.generated.h"

UCLASS()
class UNREALSHOOTER_API AShootingWeapon : public AActor, public IFirearm
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly)
	EWeaponType WeaponType = EWeaponType::Pistol;

	UPROPERTY(EditDefaultsOnly)
	EWeaponFiringType WeaponFiringType = EWeaponFiringType::Tapping;

public:	
	AShootingWeapon();
	virtual EWeaponType GetWeaponType() override { return WeaponType; }
	virtual EWeaponFiringType GetWeaponFiringType() override { return WeaponFiringType; }
	virtual bool CanShoot() override { return true; }

	virtual void Shoot(FVector Direction) override {GEngine->AddOnScreenDebugMessage(-1, 9, FColor::Cyan, "Shoot"); }
	virtual void Reload() override { }
};
