// Copyright Atennop and Krypton. All Rights Reserved.

#include "Character/ShooterCharacterWeaponHoldingComponent.h"

UShooterCharacterWeaponHoldingComponent::UShooterCharacterWeaponHoldingComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UShooterCharacterWeaponHoldingComponent::Hold(const IWeapon* Weapon)
{
	IsHoldingWeapon = true;
	
	if (Weapon != nullptr)
		HoldingWeapon.SetObject(Weapon->_getUObject());
}

void UShooterCharacterWeaponHoldingComponent::Unhold()
{
	IsAiming = false;
	IsHoldingWeapon = false;
	HoldingWeapon = nullptr;
}

void UShooterCharacterWeaponHoldingComponent::StartAim()
{
	if (HoldingWeapon == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 999, FColor::Red, "Cant start aim when have no weapon!");
		return;
	}
	
	IsAiming = true;
}

void UShooterCharacterWeaponHoldingComponent::StopAim()
{
	if (HoldingWeapon == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 999, FColor::Red, "Cant end aim when have no weapon!");
		return;
	}
	
	IsAiming = false;
}
