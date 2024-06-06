// Copyright Atennop and Krypton. All Rights Reserved.

#include "Character/Weapon/CharacterShootingComponent.h"
#include "Character/ShooterCharacter.h"
#include "Character/Weapon/CharacterWeaponRecoilingComponent.h"

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
	if (!Character->GetAimingComponent()->GetIsAiming())
		StopShooting();
	
	if (Character->IsDead() || !Character->GetWeaponHoldingComponent()->GetIsHolding() || !Character->GetWeaponHoldingComponent()->GetHoldingWeapon().GetObject()->GetClass()->ImplementsInterface(UFirearm::StaticClass()) || !Character->GetAimingComponent()->GetIsAiming())
		return;
	
	IFirearm* Weapon = Cast<IFirearm>(&*Character->GetWeaponHoldingComponent()->GetHoldingWeapon());
	if (!Weapon->GetIsEnoughAmmo())
		StopShooting();
	
	if (IsShooting && Weapon->GetData().WeaponFiringType == EWeaponFiringType::Tapping || !Weapon->GetCanShoot())
		return;

	FHitResult HitResult;
	FCollisionQueryParams CollisionParameters;
	CollisionParameters.AddIgnoredActor(GetOwner());

	const FVector StartPosition = Character->GetComponentByClass<UCameraComponent>()->GetComponentLocation();
	const FVector EndPosition = StartPosition + Character->GetControlRotation().Quaternion().GetForwardVector() * 99999;
	const bool WasHit = GetWorld()->LineTraceSingleByChannel(HitResult, StartPosition, EndPosition, ECC_Visibility, CollisionParameters);

	IsShooting = true;
	RecoilingComponent->StartRecoil();
	FVector Spread = FVector(FMath::RandRange(-Weapon->GetData().BulletSpread, Weapon->GetData().BulletSpread), 0, FMath::RandRange(-Weapon->GetData().BulletSpread, Weapon->GetData().BulletSpread));
	Weapon->Shoot((WasHit ? HitResult.Location : HitResult.TraceEnd) + Spread);
}

void UCharacterShootingComponent::StopShooting()
{
	IsShooting = false;
	
	if (IFirearm* Weapon = Cast<IFirearm>(&*Character->GetWeaponHoldingComponent()->GetHoldingWeapon()); Weapon != nullptr && Weapon->GetData().WeaponFiringType != EWeaponFiringType::Tapping)
		RecoilingComponent->StopRecoil();
}
