// Copyright Atennop and Krypton. All Rights Reserved.

#pragma once

#include "IWeapon.h"
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
	virtual void Shoot(FVector Direction) = 0;
	virtual void Reload() = 0;
};
