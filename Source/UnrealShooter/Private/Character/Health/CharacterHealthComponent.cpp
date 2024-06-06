// Copyright Atennop and Krypton. All Rights Reserved.

#include "Character/Health/CharacterHealthComponent.h"
#include "Character/ShooterCharacter.h"

UCharacterHealthComponent::UCharacterHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UCharacterHealthComponent::Die() const
{
	Character->GetCharacterMesh()->SetAllBodiesSimulatePhysics(true);
	UCameraComponent *Camera = Cast<UCameraComponent>(GetOwner()->GetComponentByClass(UCameraComponent::StaticClass()));
	Camera->AttachToComponent(ComponentToAttachCamera, FAttachmentTransformRules(EAttachmentRule::KeepWorld, false));
	
	Camera->SetRelativeTransform(CameraTransformAfterDeath);
	Character->GetController()->SetControlRotation(CameraTransformAfterDeath.Rotator());
}

void UCharacterHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	Character = Cast<AShooterCharacter>(GetOwner());
	check(Character != nullptr);
	CurrentHealth = MaxHealth;
}

void UCharacterHealthComponent::Heal(const int HealingHealth)
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
	if (IsDead())
		Die();
}
