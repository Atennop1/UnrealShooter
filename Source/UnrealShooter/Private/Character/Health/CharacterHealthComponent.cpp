// Copyright Atennop and Krypton. All Rights Reserved.

#include "Character/Health/CharacterHealthComponent.h"

#include "Camera/CameraComponent.h"
#include "Character/ShooterCharacter.h"
#include "Components/CapsuleComponent.h"

UCharacterHealthComponent::UCharacterHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UCharacterHealthComponent::Die() const
{
	if (UCameraComponent *Camera = Cast<UCameraComponent>(GetOwner()->GetComponentByClass(UCameraComponent::StaticClass())); IsValid(Camera))
	{
		Camera->AttachToComponent(ComponentToAttachCamera, FAttachmentTransformRules(EAttachmentRule::KeepWorld, false));
		Camera->SetRelativeTransform(CameraTransformAfterDeath);
	}

	Character->GetWeaponThrowingComponent()->Throw();
	Character->GetMesh()->SetAllBodiesSimulatePhysics(true);
	Character->GetCapsuleComponent()->DestroyComponent();
	Character->GetController()->SetControlRotation(CameraTransformAfterDeath.Rotator());

	FTimerHandle MeshDestroyingHandle;
	GetWorld()->GetTimerManager().SetTimer(MeshDestroyingHandle, [&]
	{
		TArray<USceneComponent*> MeshChildren;
		Character->GetMesh()->GetChildrenComponents(true, MeshChildren);
			
		for (const auto Child : MeshChildren)
			Child->DestroyComponent();
			
		Character->GetMesh()->DestroyComponent();
		Character->Destroy();
	}, TimeForMeshToDisappear, false);
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
	
	if (IsDead())
		Die();
}
