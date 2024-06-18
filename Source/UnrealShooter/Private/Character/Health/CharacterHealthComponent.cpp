// Copyright Atennop. All Rights Reserved.

#include "Character/Health/CharacterHealthComponent.h"

#include "Camera/CameraComponent.h"
#include "Character/ShooterCharacter.h"
#include "Character/Health/CharacterDyingComponent.h"
#include "Components/CapsuleComponent.h"

UCharacterHealthComponent::UCharacterHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UCharacterHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	Character = Cast<AShooterCharacter>(GetOwner());
	check(Character != nullptr);
	CurrentHealth = MaxHealth;
}

void UCharacterHealthComponent::Heal(int HealingHealth)
{
	if (CurrentHealth == MaxHealth)
		return;

	CurrentHealth += CurrentHealth + HealingHealth > MaxHealth ? MaxHealth - CurrentHealth : HealingHealth;
}

void UCharacterHealthComponent::Damage(int DamagingHealth)
{
	if (IsDead())
		return;

	CurrentHealth -= DamagingHealth;
	if (CurrentHealth < 0)
		CurrentHealth = 0;
	
	if (const auto *DyingComponent = Character->GetComponentByClass<UCharacterDyingComponent>(); DyingComponent != nullptr && IsDead())
		DyingComponent->Die();
}
