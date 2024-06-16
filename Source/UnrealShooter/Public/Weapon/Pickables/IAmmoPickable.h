// Copyright Atennop and Krypton. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Weapon/Data/WeaponType.h"
#include "IAmmoPickable.generated.h"

UINTERFACE()
class UAmmoPickable : public UInterface
{
	GENERATED_BODY()
};

class UNREALSHOOTER_API IAmmoPickable
{
	GENERATED_BODY()

public:
	virtual EWeaponType GetAmmoType() = 0;
	virtual int GetAmountOfAmmo() = 0;
};
