// Copyright Atennop and Krypton. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FirearmData.h"
#include "WeaponType.h"
#include "Interfaces/IFirearm.h"
#include "GameFramework/Actor.h"
#include "ShootingWeapon.generated.h"

UCLASS()
class UNREALSHOOTER_API AShootingWeapon : public AActor, public IFirearm
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly)
	EWeaponType WeaponType = EWeaponType::Pistol;

	UPROPERTY(BlueprintReadWrite, meta=(AllowPrivateAccess))
	USceneComponent *ShootingPoint = nullptr;

	UPROPERTY(EditDefaultsOnly)
	FFirearmData Data;
	FTimerHandle FiringDelayHandle;

	bool IsLockedByTime = false;
	bool IsEnoughAmmo = true;

protected:
	virtual void BeginPlay() override;
	
public:	
	AShootingWeapon();
	virtual EWeaponType GetWeaponType() override { return WeaponType; }
	virtual FFirearmData GetData() override { return Data; }

	virtual void Shoot(FVector Point) override;
	virtual void Reload() override;
};
