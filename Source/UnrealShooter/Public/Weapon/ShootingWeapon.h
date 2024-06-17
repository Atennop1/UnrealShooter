// Copyright Atennop and Krypton. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "IFirearm.h"
#include "Data/FirearmData.h"
#include "Data/WeaponType.h"
#include "GameFramework/Actor.h"
#include "ShootingWeapon.generated.h"

UCLASS()
class UNREALSHOOTER_API AShootingWeapon : public AActor, public IFirearm
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AActor> Bullet;
	
	UPROPERTY(EditDefaultsOnly)
	EWeaponType WeaponType = EWeaponType::Pistol;
	
	UPROPERTY(EditDefaultsOnly)
	UAnimSequence *ShootingAnimation = nullptr;
	
	UPROPERTY(EditDefaultsOnly)
	UAnimSequence *ReloadingAnimation = nullptr;

	UPROPERTY(BlueprintReadWrite, meta=(AllowPrivateAccess))
	USceneComponent *ShootingPoint = nullptr;

	UPROPERTY(EditDefaultsOnly)
	FFirearmData Data;
	FTimerHandle FiringDelayHandle;
	FTimerHandle ReloadingHandle;

	UPROPERTY(BlueprintReadWrite, meta=(AllowPrivateAccess))
	USkeletalMeshComponent *WeaponMesh = nullptr;

	int AmmoInStock;
	int AmmoInMagazine;
	
	bool IsLockedByTime = false;
	bool IsEnoughAmmo = true;
	bool IsReloading = false;

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
public:	
	AShootingWeapon();
	virtual EWeaponType GetWeaponType() override { return WeaponType; }
	virtual FFirearmData GetData() override { return Data; }
	virtual bool GetCanShoot() override { return !IsLockedByTime && IsEnoughAmmo && !IsReloading; }
	virtual bool GetIsReloading() override { return IsReloading; }
	virtual bool GetIsEnoughAmmo() override { return IsEnoughAmmo; }

	virtual void Shoot(FVector Point) override;
	virtual void Reload() override;

	virtual FFirearmState GetState() override;
	virtual void SetState(const FFirearmState NewState) override;
};
