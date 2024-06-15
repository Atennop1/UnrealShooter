// Copyright Atennop and Krypton. All Rights Reserved.

#include "Character/Weapon/CharacterWeaponHoldingComponent.h"
#include "Character/ShooterCharacter.h"
#include "Character/Weapon/CharacterAimingComponent.h"
#include "Weapon/Interfaces/IWeapon.h"

UCharacterWeaponHoldingComponent::UCharacterWeaponHoldingComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UCharacterWeaponHoldingComponent::BeginPlay()
{
	Super::BeginPlay();
	Character = Cast<AShooterCharacter>(GetOwner());
	check(Character != nullptr)
}

void UCharacterWeaponHoldingComponent::Hold(const TScriptInterface<IWeapon> Weapon)
{
	if (Character->IsDead() || Weapon == nullptr || !WeaponsToSockets.Contains(Weapon.GetObject()->GetClass()))
		return;
	
	IsHoldingWeapon = true;
	HoldingWeapon = Weapon;
	Cast<AActor>(Weapon.GetObject())->AttachToComponent(Character->GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), WeaponsToSockets[Weapon.GetObject()->GetClass()]);
}

void UCharacterWeaponHoldingComponent::Unhold()
{
	if (Character->IsDead())
		return;
	
	Character->GetAimingComponent()->StopAim();
	GetWorld()->DestroyActor(Cast<AActor>(HoldingWeapon.GetObject()));
	IsHoldingWeapon = false;
	HoldingWeapon = nullptr;
}
