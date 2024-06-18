// Copyright Atennop. All Rights Reserved.

#pragma once

#include "Weapon/Data/WeaponType.h"
#include "UObject/Interface.h"
#include "IWeapon.generated.h"

UINTERFACE(MinimalAPI, BlueprintType, meta=(CannotImplementInterfaceInBlueprint))
class UWeapon : public UInterface
{
	GENERATED_BODY()
};

class UNREALSHOOTER_API IWeapon
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	virtual EWeaponType GetWeaponType() = 0;
};
