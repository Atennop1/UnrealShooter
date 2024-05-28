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

void AShootingWeapon::Shoot(FVector Direction)
{
	if (!CanShoot)
		return;
	
	--AmmoInMagazine;
	CanShoot = false;
	IsLockedByTime = true;
	IsEnoughAmmo = AmmoInMagazine > 0;

	GetWorld()->GetTimerManager().SetTimer(FiringDelayHandle, [&]
	{
		IsLockedByTime = false;
		CanShoot = IsEnoughAmmo;
	}, Data.FiringDelayInSeconds, false);
	
	FHitResult HitResult;
	FCollisionQueryParams CollisionParameters;
	CollisionParameters.AddIgnoredActor(GetOwner());
	const bool WasHit = GetWorld()->LineTraceSingleByChannel(HitResult, ShootingPoint->GetComponentLocation(), ShootingPoint->GetComponentLocation() + Direction * 99999, ECC_Visibility, CollisionParameters);
	WeaponMesh->PlayAnimation(ShootingAnimation, false);

	if (WasHit)
	{
		// collision logic
	}
}

void AShootingWeapon::Reload()
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
