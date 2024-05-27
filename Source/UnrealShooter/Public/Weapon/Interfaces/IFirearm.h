// Copyright Atennop and Krypton. All Rights Reserved.

#pragma once

#include "IWeapon.h"
#include "Weapon/FirearmData.h"
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
	virtual FFirearmData GetData() = 0;
	
	virtual void Shoot(FVector Point) = 0;
	virtual void Reload() = 0;
};
