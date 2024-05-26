// Copyright Atennop and Krypton. All Rights Reserved.

#include "Character/CharacterWeaponThrowingComponent.h"

#include "Character/ShooterCharacter.h"

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
	if (!Character->GetWeaponHoldingComponent()->GetIsHoldingWeapon() || !WeaponsToPickables.Contains(Character->GetWeaponHoldingComponent()->GetHoldingWeapon().GetObject()->GetClass()))
		return;

	const FRotator SpawnRotation = FRotator(0, Character->GetControlRotation().Yaw, 0);
	const FVector SpawnPosition = Character->GetComponentByClass<UCameraComponent>()->GetComponentLocation() + Character->GetControlRotation().Quaternion().GetForwardVector() * 100;
	const AActor *SpawnedPickable = GetWorld()->SpawnActor(WeaponsToPickables[Character->GetWeaponHoldingComponent()->GetHoldingWeapon().GetObject()->GetClass()], &SpawnPosition, &SpawnRotation);
	Character->GetWeaponHoldingComponent()->Unhold();

	if (const auto PrimitiveComponent = SpawnedPickable->GetComponentByClass<UPrimitiveComponent>(); PrimitiveComponent != nullptr)
		PrimitiveComponent->AddForce(Character->GetControlRotation().Quaternion().GetForwardVector() * DefaultThrowingForce * PrimitiveComponent->GetMass());
}