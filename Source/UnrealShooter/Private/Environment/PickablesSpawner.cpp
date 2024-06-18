// Copyright Atennop. All Rights Reserved.

#include "Environment/PickablesSpawner.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

APickablesSpawner::APickablesSpawner()
{
	PrimaryActorTick.bCanEverTick = true;
}

void APickablesSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	ElapsedTime += DeltaTime;
	const ACharacter *PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	
	if (ElapsedTime < StartDelay || IsValid(LastSpawnedPickable) || !IsValid(PlayerCharacter))
		return;
	
	FHitResult Hit;
	UKismetSystemLibrary::SphereTraceSingle(GetWorld(), GetActorLocation(), PlayerCharacter->GetActorLocation(), SphereTraceRadius, TraceTypeQuery2, false, {}, EDrawDebugTrace::None, Hit, true);
	if (Hit.GetActor() == PlayerCharacter)
		return;
	
	ElapsedTime = 0;
	StartDelay = TimeForSpawn;
	const FVector SpawnPosition = GetActorLocation();
	const FRotator SpawnRotation = GetActorRotation();
	LastSpawnedPickable = GetWorld()->SpawnActor(PickablesToSpawn[FMath::RandRange(0, PickablesToSpawn.Num() - 1)], &SpawnPosition, &SpawnRotation);
}

