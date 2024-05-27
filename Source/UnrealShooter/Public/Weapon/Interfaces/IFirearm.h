// Copyright Atennop and Krypton. All Rights Reserved.

#pragma once

#include "IWeapon.h"
#include "Weapon/WeaponFiringType.h"
#include "IFirearm.generated.h"

UINTERFACE(MinimalAPI, BlueprintType, meta=(CannotImplementInterfaceInBlueprint))
class UFirearm : public UWeapon
{
	GENERATED_BODY()
};

class UNREALSHOOTER_API IFirearm : public IWeapon
{
	GENERATED_BODY()

public:
	virtual EWeaponFiringType GetWeaponFiringType() = 0;
	virtual bool CanShoot() = 0;
	
	virtual void Shoot(FVector Direction) = 0;
	virtual void Reload() = 0;
};
