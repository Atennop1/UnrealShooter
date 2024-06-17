// Copyright Atennop and Krypton. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FirearmState.generated.h"

USTRUCT(BlueprintType)
struct UNREALSHOOTER_API FFirearmState
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	int AmmoInMagazine = 0;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	int AmmoInStock = 0;

	void Init(const int NewAmmoInMagazine, const int NewAmmoInStock)
	{
		AmmoInMagazine = NewAmmoInMagazine;
		AmmoInStock = NewAmmoInStock;
	}
};
