// Copyright Atennop. All Rights Reserved.

#include "Enemy/EnemyCharacter.h"

AEnemyCharacter::AEnemyCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	check(PatrollingComponent != nullptr)
}
