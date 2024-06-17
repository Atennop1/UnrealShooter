// Copyright Atennop and Krypton. All Rights Reserved.

#pragma once

#include "IWeapon.h"
#include "Weapon/Data/FirearmData.h"
#include "Weapon/Data/FirearmState.h"
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
	virtual bool GetCanShoot() = 0;
	virtual bool GetIsReloading() = 0;
	virtual bool GetIsEnoughAmmo() = 0;
	
	virtual void Shoot(FVector Point) = 0;
	virtual void Reload() = 0;

	UFUNCTION(BlueprintCallable)
	virtual FFirearmState GetState() = 0;
	virtual void SetState(FFirearmState State) = 0;
};
