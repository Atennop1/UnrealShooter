// Copyright Atennop and Krypton. All Rights Reserved.

#include "Character/CharacterAimingComponent.h"
#include "Character/ShooterCharacter.h"

UCharacterAimingComponent::UCharacterAimingComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UCharacterAimingComponent::BeginPlay()
{
	Super::BeginPlay();
	Character = Cast<AShooterCharacter>(GetOwner());
	check(Character != nullptr)
}

void UCharacterAimingComponent::StartAim()
{
	if (Character->GetWeaponHoldingComponent()->GetHoldingWeapon() == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 999, FColor::Red, "Cant start aim when have no weapon!");
		return;
	}
	
	IsAiming = true;
}

void UCharacterAimingComponent::StopAim()
{
	if (Character->GetWeaponHoldingComponent()->GetHoldingWeapon() == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 999, FColor::Red, "Cant end aim when have no weapon!");
		return;
	}
	
	IsAiming = false;
}