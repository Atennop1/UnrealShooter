// Copyright Atennop and Krypton. All Rights Reserved.

#include "Character/Weapon/CharacterWeaponThrowingComponent.h"
#include "Camera/CameraComponent.h"
#include "Character/ShooterCharacter.h"
#include "Character/Weapon/CharacterWeaponHoldingComponent.h"
#include "Weapon/Interfaces/IFirearm.h"
#include "Weapon/Interfaces/IFirearmPickable.h"

UCharacterWeaponThrowingComponent::UCharacterWeaponThrowingComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UCharacterWeaponThrowingComponent::BeginPlay()
{
	Super::BeginPlay();
	Character = Cast<AShooterCharacter>(GetOwner());
	check(Character)
}

void UCharacterWeaponThrowingComponent::Throw()
{
	if (Character->IsDead() || !Character->GetWeaponHoldingComponent()->GetIsHolding() || !WeaponsToPickables.Contains(Character->GetWeaponHoldingComponent()->GetHoldingWeapon().GetObject()->GetClass()))
		return;

	if (const FFirearmState HoldingWeaponState = Cast<IFirearm>(Character->GetWeaponHoldingComponent()->GetHoldingWeapon().GetObject())->GetState(); HoldingWeaponState.AmmoInMagazine == 0 && HoldingWeaponState.AmmoInStock == 0)
	{
		Character->GetWeaponHoldingComponent()->Unhold();
		return;
	}
	
	const FRotator SpawnRotation = FRotator(FMath::RandRange(-20.f, 20.f), Character->GetControlRotation().Yaw + FMath::RandRange(-20.f, 20.f), FMath::RandRange(-20.f, 20.f));
	const FVector SpawnPosition = Character->GetComponentByClass<UCameraComponent>()->GetComponentLocation() + Character->GetControlRotation().Quaternion().GetForwardVector() * StartDistance;
	AActor *SpawnedPickable = GetWorld()->SpawnActor(WeaponsToPickables[Character->GetWeaponHoldingComponent()->GetHoldingWeapon().GetObject()->GetClass()], &SpawnPosition, &SpawnRotation);

	if (const auto PrimitiveComponent = SpawnedPickable->GetComponentByClass<UPrimitiveComponent>(); PrimitiveComponent != nullptr)
		PrimitiveComponent->AddForce(Character->GetControlRotation().Quaternion().GetForwardVector() * DefaultThrowingForce * PrimitiveComponent->GetMass());

	if (const auto FirearmPickable = Cast<IFirearmPickable>(SpawnedPickable); FirearmPickable != nullptr)
		FirearmPickable->SetState(Cast<IFirearm>(Character->GetWeaponHoldingComponent()->GetHoldingWeapon().GetObject())->GetState());

	Character->GetWeaponHoldingComponent()->Unhold();
}