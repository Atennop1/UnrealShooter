// Copyright Atennop and Krypton. All Rights Reserved.

#include "Character/Weapon/CharacterShootingComponent.h"
#include "Character/ShooterCharacter.h"

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
	if (Weapon->GetData().WeaponFiringType == EWeaponFiringType::Tapping && IsShooting || !Weapon->GetData().CanShoot)
		return;

	FHitResult HitResult;
	FCollisionQueryParams CollisionParameters;
	CollisionParameters.AddIgnoredActor(GetOwner());
	
	const FVector StartPosition = Character->GetComponentByClass<UCameraComponent>()->GetComponentLocation();
	const FVector EndPosition = StartPosition + Character->GetControlRotation().Quaternion().GetForwardVector() * 99999;
	const bool WasHit = GetWorld()->LineTraceSingleByChannel(HitResult, StartPosition, EndPosition, ECC_Visibility, CollisionParameters);
	
	Weapon->Shoot(WasHit ? HitResult.Location : HitResult.TraceEnd);
	IsShooting = true;
}

void UCharacterShootingComponent::StopShooting()
{
	IsShooting = false;
}

void UCharacterShootingComponent::Reload() const
{
	if (!Character->GetWeaponHoldingComponent()->GetIsHolding() || !Character->GetWeaponHoldingComponent()->GetHoldingWeapon().GetObject()->GetClass()->ImplementsInterface(UFirearm::StaticClass()))
		return;

	IFirearm* Weapon = Cast<IFirearm>(&*Character->GetWeaponHoldingComponent()->GetHoldingWeapon());
	Weapon->Reload();
}
