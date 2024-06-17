// Copyright Atennop and Krypton. All Rights Reserved.

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
	
	if (ElapsedTime < StartDelay || IsValid(LastSpawnedPickable))
		return;
	
	FHitResult Hit;
	GetWorld()->LineTraceSingleByChannel(Hit, GetActorLocation(), UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)->GetActorLocation(), ECC_Visibility);
	if (Hit.GetActor() == UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))
		return;
	
	ElapsedTime = 0;
	StartDelay = TimeForSpawn;
	const FVector SpawnPosition = GetActorLocation();
	const FRotator SpawnRotation = GetActorRotation();
	LastSpawnedPickable = GetWorld()->SpawnActor(PickablesToSpawn[FMath::RandRange(0, PickablesToSpawn.GetAllocatedSize() / PickablesToSpawn.GetTypeSize() - 1)], &SpawnPosition, &SpawnRotation);
}

