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

	FOnTimelineFloat OnUpdated;
	OnUpdated.BindUFunction(this, "OnSpreadUpdated");
	SpreadingTimeline.AddInterpFloat(SpreadCurve, OnUpdated);
}

void UCharacterShootingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	SpreadingTimeline.TickTimeline(DeltaTime);
}

void UCharacterShootingComponent::OnSpreadUpdated(float Alpha)
{
	SpreadingCoefficient = Alpha;
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
	SpreadingTimeline.Play();
	FVector Spread = FVector(FMath::RandRange(-Weapon->GetData().MaxBulletSpread, Weapon->GetData().MaxBulletSpread), 0, FMath::RandRange(-Weapon->GetData().MaxBulletSpread, Weapon->GetData().MaxBulletSpread));
	Weapon->Shoot((WasHit ? HitResult.Location : HitResult.TraceEnd) + Spread * SpreadingCoefficient);
}

void UCharacterShootingComponent::StopShooting()
{
	IsShooting = false;
	SpreadingTimeline.Stop();
	SpreadingTimeline.SetNewTime(0);
	
	if (IFirearm* Weapon = Cast<IFirearm>(&*Character->GetWeaponHoldingComponent()->GetHoldingWeapon()); Weapon != nullptr && Weapon->GetData().WeaponFiringType != EWeaponFiringType::Tapping)
		RecoilingComponent->StopRecoil();
}
