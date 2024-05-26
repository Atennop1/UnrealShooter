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
	if (Weapon == nullptr || !WeaponsToSockets.Contains(Weapon.GetObject()->GetClass()))
		return;
	
	IsHoldingWeapon = true;
	HoldingWeapon = Weapon;

	const FAttachmentTransformRules Rules = FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true);
	Cast<AActor>(Weapon.GetObject())->AttachToComponent(Character->GetCharacterMesh(), Rules, WeaponsToSockets[Weapon.GetObject()->GetClass()]);
}

void UCharacterWeaponHoldingComponent::Unhold()
{
	Character->GetAimingComponent()->StopAim();
	GetWorld()->DestroyActor(Cast<AActor>(HoldingWeapon.GetObject()));
	IsHoldingWeapon = false;
	HoldingWeapon = nullptr;
}
