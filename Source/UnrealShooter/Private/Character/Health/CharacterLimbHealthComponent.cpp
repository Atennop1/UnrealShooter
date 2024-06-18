// Copyright Atennop. All Rights Reserved.

#include "Character/Health/CharacterLimbHealthComponent.h"

UCharacterLimbHealthComponent::UCharacterLimbHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UCharacterLimbHealthComponent::Damage(int DamagingHealth)
{
	HealthComponent->Damage(DamagingHealth * DamageMultiplier);
}

void UCharacterLimbHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	HealthComponent = Cast<UCharacterHealthComponent>(GetOwner()->GetComponentByClass(UCharacterHealthComponent::StaticClass()));
	check(HealthComponent);
}
