// Copyright Atennop. All Rights Reserved.

#include "Enemy/Components/EnemyCharacterHealthComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Perception/AISense_Damage.h"

UEnemyCharacterHealthComponent::UEnemyCharacterHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UEnemyCharacterHealthComponent::Damage(int DamagingHealth)
{
	Super::Damage(DamagingHealth);
	UAISense_Damage::ReportDamageEvent(GetWorld(), GetOwner(), UGameplayStatics::GetPlayerCharacter(GetWorld(), 0), DamagingHealth, GetOwner()->GetActorLocation(), GetOwner()->GetActorLocation());
}
