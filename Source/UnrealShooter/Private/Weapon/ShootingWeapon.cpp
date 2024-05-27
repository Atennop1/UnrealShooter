// Copyright Atennop and Krypton. All Rights Reserved.

#include "Weapon/ShootingWeapon.h"

#include "Kismet/KismetStringLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

AShootingWeapon::AShootingWeapon() : Data()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AShootingWeapon::BeginPlay()
{
	Super::BeginPlay();
	check(ShootingPoint);
	Data.CurrentAmmo = Data.MaxAmmo;
}

void AShootingWeapon::Shoot(FVector Point)
{
	if (!Data.CanShoot)
		return;
	
	FVector Direction = ShootingPoint->GetComponentLocation() - Point;
	UKismetSystemLibrary::DrawDebugLine(GetWorld(),ShootingPoint->GetComponentLocation(), Point, FColor::Red, 10);

	--Data.CurrentAmmo;
	Data.CanShoot = false;
	IsLockedByTime = true;
	IsEnoughAmmo = Data.CurrentAmmo > 0;

	GetWorld()->GetTimerManager().SetTimer(FiringDelayHandle, [&]
	{
		IsLockedByTime = false;
		Data.CanShoot = IsEnoughAmmo;
	}, Data.FiringDelayInSeconds, false);
}

void AShootingWeapon::Reload()
{
	Data.CurrentAmmo = Data.MaxAmmo;
	Data.CanShoot = !IsLockedByTime;
	IsEnoughAmmo = true;
}
