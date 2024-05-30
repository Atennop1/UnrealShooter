// Copyright Atennop and Krypton. All Rights Reserved.

#include "Character/Weapon/CharacterShootingComponent.h"
#include "Character/ShooterCharacter.h"
#include "Character/Weapon/CharacterWeaponRecoilingComponent.h"

UCharacterShootingComponent::UCharacterShootingComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UCharacterShootingComponent::BeginPlay()
{
	Super::BeginPlay();
	Character = Cast<AShooterCharacter>(GetOwner());
	check(Character != nullptr);
}

void UCharacterShootingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (IFirearm* Weapon = Cast<IFirearm>(&*Character->GetWeaponHoldingComponent()->GetHoldingWeapon()); Weapon != nullptr && !Weapon->GetCanShoot())
		StopShooting();
}

void UCharacterShootingComponent::Reload() const
{
	if (!Character->GetWeaponHoldingComponent()->GetIsHolding() || !Character->GetWeaponHoldingComponent()->GetHoldingWeapon().GetObject()->GetClass()->ImplementsInterface(UFirearm::StaticClass()))
		return;

	if (IFirearm* Weapon = Cast<IFirearm>(&*Character->GetWeaponHoldingComponent()->GetHoldingWeapon()); !Weapon->GetIsReloading())
		Weapon->Reload();
}

void UCharacterShootingComponent::StartShooting()
{
	if (!Character->GetWeaponHoldingComponent()->GetIsHolding() || !Character->GetWeaponHoldingComponent()->GetHoldingWeapon().GetObject()->GetClass()->ImplementsInterface(UFirearm::StaticClass()) || !Character->GetAimingComponent()->GetIsAiming())
		return;

	IFirearm* Weapon = Cast<IFirearm>(&*Character->GetWeaponHoldingComponent()->GetHoldingWeapon());
	if (!CanShootNow || !Weapon->GetCanShoot())
		return;

	FHitResult HitResult;
	FCollisionQueryParams CollisionParameters;
	CollisionParameters.AddIgnoredActor(GetOwner());

	const FVector StartPosition = Character->GetComponentByClass<UCameraComponent>()->GetComponentLocation();
	const FVector EndPosition = StartPosition + Character->GetControlRotation().Quaternion().GetForwardVector() * 99999;
	const bool WasHit = GetWorld()->LineTraceSingleByChannel(HitResult, StartPosition, EndPosition, ECC_Visibility, CollisionParameters);

	RecoilingComponent->StartRecoil();
	Weapon->Shoot(WasHit ? HitResult.Location : HitResult.TraceEnd);

	if (Weapon->GetData().WeaponFiringType == EWeaponFiringType::Tapping)
	{
		CanShootNow = false;
		RecoilingComponent->StopRecoil();
	}
}

void UCharacterShootingComponent::StopShooting()
{
	CanShootNow = true;
	RecoilingComponent->StopRecoil();
}
