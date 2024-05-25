// Copyright Atennop and Krypton. All Rights Reserved.

#include "Character/ShooterCharacterAimingComponent.h"
#include "Character/ShooterCharacter.h"

UShooterCharacterAimingComponent::UShooterCharacterAimingComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UShooterCharacterAimingComponent::BeginPlay()
{
	Super::BeginPlay();
	Character = Cast<AShooterCharacter>(GetOwner());
	check(Character != nullptr)
}

void UShooterCharacterAimingComponent::StartAim()
{
	if (Character->GetWeaponHoldingComponent()->GetHoldingWeapon() == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 999, FColor::Red, "Cant start aim when have no weapon!");
		return;
	}
	
	IsAiming = true;
}

void UShooterCharacterAimingComponent::StopAim()
{
	if (Character->GetWeaponHoldingComponent()->GetHoldingWeapon() == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 999, FColor::Red, "Cant end aim when have no weapon!");
		return;
	}
	
	IsAiming = false;
}