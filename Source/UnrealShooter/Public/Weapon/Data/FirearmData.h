// Copyright Atennop and Krypton. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "WeaponFiringType.h"
#include "FirearmData.generated.h"

USTRUCT()
struct UNREALSHOOTER_API FFirearmData
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly)
	EWeaponFiringType WeaponFiringType;

	UPROPERTY(EditDefaultsOnly)
	int MaxAmmoInMagazine;

	UPROPERTY(EditDefaultsOnly)
	float FiringDelayInSeconds;

	UPROPERTY(EditDefaultsOnly)
	float MaxBulletSpread;

	UPROPERTY(EditDefaultsOnly)
	UCurveVector *RecoilingCurve;
};
