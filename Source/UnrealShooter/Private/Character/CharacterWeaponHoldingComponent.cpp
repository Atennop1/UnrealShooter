// Copyright Atennop and Krypton. All Rights Reserved.

#include "Character/CharacterWeaponHoldingComponent.h"
#include "Character/ShooterCharacter.h"
#include "Kismet/KismetSystemLibrary.h"
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
	if (Weapon == nullptr)
		return;
	
	IsHoldingWeapon = true;
	HoldingWeapon = Weapon;

	const FAttachmentTransformRules Rules = FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true);
	Cast<AActor>(Weapon.GetObject())->AttachToComponent(Character->GetCharacterMesh(), Rules, ClassToSocket[Weapon.GetObject()->GetClass()]);
}

void UCharacterWeaponHoldingComponent::Unhold()
{
	Character->GetAimingComponent()->StopAim();
	IsHoldingWeapon = false;
	HoldingWeapon = nullptr;
}
