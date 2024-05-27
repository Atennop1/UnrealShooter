// Copyright Atennop and Krypton. All Rights Reserved.

#include "Character/Weapon/CharacterShootingComponent.h"
#include "Character/ShooterCharacter.h"
#include "Kismet/KismetStringLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

UCharacterShootingComponent::UCharacterShootingComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UCharacterShootingComponent::BeginPlay()
{
	Super::BeginPlay();
	Character = Cast<AShooterCharacter>(GetOwner());
	check(Character != nullptr);
}

void UCharacterShootingComponent::StartShooting()
{
	if (!Character->GetWeaponHoldingComponent()->GetIsHolding() || !Character->GetWeaponHoldingComponent()->GetHoldingWeapon().GetObject()->GetClass()->ImplementsInterface(UFirearm::StaticClass()) || !Character->GetAimingComponent()->GetIsAiming())
		return;

	IFirearm* Weapon = Cast<IFirearm>(&*Character->GetWeaponHoldingComponent()->GetHoldingWeapon());
	if (Weapon->GetWeaponFiringType() == EWeaponFiringType::Tapping && IsShooting || !Weapon->CanShoot())
		return;

	Weapon->Shoot(FVector(0, 0, 0));
	IsShooting = true;
}

void UCharacterShootingComponent::StopShooting()
{
	IsShooting = false;
}
