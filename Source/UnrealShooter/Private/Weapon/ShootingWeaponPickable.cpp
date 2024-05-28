// Copyright Atennop and Krypton. All Rights Reserved.

#include "Weapon/ShootingWeaponPickable.h"

AShootingWeaponPickable::AShootingWeaponPickable() : State(0, 0)
{
	PrimaryActorTick.bCanEverTick = false;
}

FFirearmState AShootingWeaponPickable::GetState()
{
	return State;
}

void AShootingWeaponPickable::SetState(const FFirearmState NewState)
{
	State = NewState;
}
