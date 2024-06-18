// Copyright Atennop and Krypton. All Rights Reserved.

#include "Character/Weapon/CharacterShootingComponent.h"
#include "Camera/CameraComponent.h"
#include "Character/ShooterCharacter.h"
#include "Character/Weapon/CharacterWeaponRecoilingComponent.h"
#include "Perception/AISense_Hearing.h"
#include "Weapon/IFirearm.h"

UCharacterShootingComponent::UCharacterShootingComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UCharacterShootingComponent::BeginPlay()
{
	Super::BeginPlay();
	Character = Cast<AShooterCharacter>(GetOwner());
	check(Character != nullptr);

	FOnTimelineFloat OnUpdated;
	OnUpdated.BindUFunction(this, "OnSpreadUpdated");
	SpreadingTimeline.AddInterpFloat(SpreadCurve, OnUpdated);
}

void UCharacterShootingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	SpreadingTimeline.TickTimeline(DeltaTime);

	IFirearm* Weapon = Cast<IFirearm>(&*Character->GetWeaponHoldingComponent()->GetHoldingWeapon());
	if (!Character->GetAimingComponent()->GetIsAiming() || !Weapon->GetIsEnoughAmmo() || Weapon->GetIsReloading())
	{
		StopShooting();
		return;
	}

	if (Weapon->GetData().WeaponFiringType != EWeaponFiringType::Tapping && Weapon->GetCanShoot() && IsShooting)
		Shoot();
}

void UCharacterShootingComponent::StartShooting()
{
	if (IFirearm* Weapon = Cast<IFirearm>(&*Character->GetWeaponHoldingComponent()->GetHoldingWeapon()); !Character->IsDead() && Character->GetWeaponHoldingComponent()->GetIsHolding() &&  Weapon != nullptr && Weapon->GetCanShoot() && Character->GetAimingComponent()->GetIsAiming())
	{
		IsShooting = true;
		Shoot();
	}
}

void UCharacterShootingComponent::StopShooting()
{
	IsShooting = false;
	SpreadingTimeline.Stop();
	SpreadingTimeline.SetNewTime(0);
	
	if (IFirearm* Weapon = Cast<IFirearm>(&*Character->GetWeaponHoldingComponent()->GetHoldingWeapon()); Weapon != nullptr && Weapon->GetData().WeaponFiringType != EWeaponFiringType::Tapping)
		RecoilingComponent->StopRecoil();
}

void UCharacterShootingComponent::Shoot()
{
	if (Character->IsDead())
		return;
	
	FHitResult HitResult;
	FCollisionQueryParams CollisionParameters;
	CollisionParameters.AddIgnoredActor(GetOwner());

	IFirearm* Weapon = Cast<IFirearm>(&*Character->GetWeaponHoldingComponent()->GetHoldingWeapon());
	const FVector StartPosition = Character->GetComponentByClass<UCameraComponent>()->GetComponentLocation();
	const FVector EndPosition = StartPosition + Character->GetControlRotation().Quaternion().GetForwardVector() * 99999;
	const bool WasHit = GetWorld()->LineTraceSingleByChannel(HitResult, StartPosition, EndPosition, ECC_Visibility, CollisionParameters);

	if (IsMakingNoise)
		UAISense_Hearing::ReportNoiseEvent(GetWorld(), StartPosition, 1, Character);
	
	SpreadingTimeline.Play();
	RecoilingComponent->StartRecoil();
	FVector Spread = FVector(FMath::RandRange(-Weapon->GetData().MaxBulletSpread, Weapon->GetData().MaxBulletSpread), 0, FMath::RandRange(-Weapon->GetData().MaxBulletSpread, Weapon->GetData().MaxBulletSpread));
	Weapon->Shoot((WasHit ? HitResult.Location : HitResult.TraceEnd) + Spread * SpreadingCoefficient);
}
