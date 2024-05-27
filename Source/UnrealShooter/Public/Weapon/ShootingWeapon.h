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
	EWeaponType WeaponType;

public:	
	AShootingWeapon();
	EWeaponType GetWeaponType() override { return WeaponType; }

	virtual void Shoot(FVector Direction) override { }
	virtual void Reload() override { }
};
