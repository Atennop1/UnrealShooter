// Copyright Atennop. All Rights Reserved.

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
	const ACharacter *PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	
	if (IsValid(SpawnedEnemy) || !CanSpawn || !IsValid(PlayerCharacter))
		return;
	
	FHitResult Hit;
	UKismetSystemLibrary::SphereTraceSingle(GetWorld(), GetActorLocation(), PlayerCharacter->GetActorLocation(), SphereTraceRadius, TraceTypeQuery2, false, {}, EDrawDebugTrace::None, Hit, true);
	if (Hit.GetActor() == PlayerCharacter)
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

