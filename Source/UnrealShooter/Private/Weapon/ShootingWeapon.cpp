// Copyright Atennop and Krypton. All Rights Reserved.

#include "Weapon/ShootingWeapon.h"

AShootingWeapon::AShootingWeapon() : Data(), AmmoInStock(), AmmoInMagazine()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AShootingWeapon::BeginPlay()
{
	Super::BeginPlay();
	check(ShootingPoint);
	check(WeaponMesh);
}

void AShootingWeapon::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	GetWorld()->GetTimerManager().ClearTimer(FiringDelayHandle);
	GetWorld()->GetTimerManager().ClearTimer(ReloadingHandle);
}

void AShootingWeapon::Shoot(FVector Point)
{
	if (!CanShoot)
		return;
	
	--AmmoInMagazine;
	CanShoot = false;
	IsLockedByTime = true;
	IsEnoughAmmo = AmmoInMagazine > 0;

	const FVector SpawnLocation = ShootingPoint->GetComponentLocation();
	const FRotator SpawnRotation = (Point - ShootingPoint->GetComponentLocation()).Rotation();
	GetWorld()->SpawnActor(Bullet, &SpawnLocation, &SpawnRotation);
	
	WeaponMesh->PlayAnimation(ShootingAnimation, false);
	GetWorld()->GetTimerManager().SetTimer(FiringDelayHandle, [&]
	{
		IsLockedByTime = false;
		CanShoot = IsEnoughAmmo;
	}, Data.FiringDelayInSeconds, false);
}

void AShootingWeapon::Reload()
{
	if (AmmoInMagazine == 0 && AmmoInStock == 0)
		return;

	CanShoot = false;
	WeaponMesh->PlayAnimation(ReloadingAnimation, false);
	
	GetWorld()->GetTimerManager().SetTimer(ReloadingHandle, [&]
	{
		if (AmmoInStock - (Data.MaxAmmoInMagazine - AmmoInMagazine) >= 0)
		{
			AmmoInStock -= Data.MaxAmmoInMagazine - AmmoInMagazine;
			AmmoInMagazine = Data.MaxAmmoInMagazine;
		}
		else
		{
			AmmoInMagazine += AmmoInStock;
			AmmoInStock = 0;
		}
	
		IsEnoughAmmo = AmmoInMagazine > 0;
		CanShoot = !IsLockedByTime && IsEnoughAmmo;
	}, ReloadingAnimation->GetPlayLength(), false);
}

FFirearmState AShootingWeapon::GetState()
{
	FFirearmState CurrentState;
	CurrentState.Init(AmmoInMagazine, AmmoInStock);
	return CurrentState;
}

void AShootingWeapon::SetState(const FFirearmState NewState)
{
	AmmoInMagazine = NewState.AmmoInMagazine;
	AmmoInStock = NewState.AmmoInStock;

	if (AmmoInMagazine > Data.MaxAmmoInMagazine)
		AmmoInStock += AmmoInMagazine - Data.MaxAmmoInMagazine;

	CanShoot = AmmoInMagazine > 0;
}
