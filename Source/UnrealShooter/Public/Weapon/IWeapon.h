// Copyright Atennop and Krypton. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "WeaponType.h"
#include "UObject/Interface.h"
#include "IWeapon.generated.h"

UINTERFACE(MinimalAPI, Meta=(CannotImplementInterfaceInBlueprint))
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
	
	virtual void Shoot(FVector Direction) = 0;
	virtual void Reload() = 0;
};
