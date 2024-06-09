// Copyright Atennop and Krypton. All Rights Reserved.

#include "Enemy/Movement/EnemyCharacterRotatingComponent.h"

UEnemyCharacterRotatingComponent::UEnemyCharacterRotatingComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UEnemyCharacterRotatingComponent::Rotate(const FVector2D Input)
{
	
}

FVector UEnemyCharacterRotatingComponent::GetLocationCameraPointingAt()
{
	return LocationCameraPointingAt;
}

FVector UEnemyCharacterRotatingComponent::GetInputOfThisFrame()
{
	return FVector::Zero();
}
