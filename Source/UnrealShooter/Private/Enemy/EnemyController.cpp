// Copyright Atennop and Krypton. All Rights Reserved.

#include "Enemy/EnemyController.h"

AEnemyController::AEnemyController()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AEnemyController::BeginPlay()
{
	Super::BeginPlay();
	RunBehaviorTree(BehaviorTree);
}

