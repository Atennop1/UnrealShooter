// Copyright Atennop and Krypton. All Rights Reserved.

#include "Environment/EnemiesSpawner.h"

#include "Kismet/GameplayStatics.h"

AEnemiesSpawner::AEnemiesSpawner()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AEnemiesSpawner::BeginPlay()
{
	Super::BeginPlay();
	FTimerHandle SpawnTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandle, [&] { CanSpawn = true; }, StartDelay, false);
}

void AEnemiesSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (IsValid(SpawnedEnemy) || !CanSpawn)
		return;
	
	FHitResult Hit;
	GetWorld()->LineTraceSingleByChannel(Hit, GetActorLocation(), UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)->GetActorLocation(), ECC_Visibility);
	if (Hit.GetActor() == UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))
		return;

	if (IsValid(SpawnedController))
		SpawnedController->Destroy();
	
	const FVector SpawnPosition = GetActorLocation();
	const FRotator SpawnRotation = GetActorRotation();
	SpawnedController = Cast<AEnemyController>(GetWorld()->SpawnActor(ControllerToSpawn, &SpawnPosition, &SpawnRotation));
	SpawnedEnemy = Cast<AEnemyCharacter>(GetWorld()->SpawnActor(EnemyToSpawn, &SpawnPosition, &SpawnRotation));
	
	SpawnedEnemy->GetPatrollingComponent()->Init(SplineActor->GetComponentByClass<USplineComponent>());
	SpawnedController->Possess(SpawnedEnemy);
}

