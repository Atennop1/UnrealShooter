// Copyright Atennop. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "IAmmoPickable.h"
#include "GameFramework/Actor.h"
#include "DefaultAmmoPickable.generated.h"

UCLASS()
class UNREALSHOOTER_API ADefaultAmmoPickable : public AActor, public IAmmoPickable
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly)
	EWeaponType AmmoType;

	UPROPERTY(EditDefaultsOnly)
	int AmountOfAmmo = 30;

public:
	ADefaultAmmoPickable();

	virtual EWeaponType GetAmmoType() override { return AmmoType; }
	virtual int GetAmountOfAmmo() override { return AmountOfAmmo; }
};
