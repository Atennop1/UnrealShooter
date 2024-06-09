// Copyright Atennop and Krypton. All Rights Reserved.

#include "Enemy/Movement/EnemyCharacterCrouchingComponent.h"

UEnemyCharacterCrouchingComponent::UEnemyCharacterCrouchingComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

bool UEnemyCharacterCrouchingComponent::GetIsCrouching()
{
	return false;
}

void UEnemyCharacterCrouchingComponent::StartCrouching()
{
	
}

void UEnemyCharacterCrouchingComponent::StopCrouching()
{
	
}
