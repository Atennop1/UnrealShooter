// Copyright Atennop. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Enemy/EnemyCharacter.h"
#include "Enemy/EnemyController.h"
#include "GameFramework/Actor.h"
#include "EnemiesSpawner.generated.h"

UCLASS()
class UNREALSHOOTER_API AEnemiesSpawner : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere)
	float StartDelay = 5;
	
	UPROPERTY(EditAnywhere)
	float SphereTraceRadius = 20;
	
	UPROPERTY(EditAnywhere)
	AActor *SplineActor = nullptr;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<AEnemyCharacter> EnemyToSpawn;
	bool CanSpawn = false;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AEnemyController> ControllerToSpawn;

	UPROPERTY()
	AEnemyCharacter *SpawnedEnemy = nullptr;

	UPROPERTY()
	AEnemyController *SpawnedController = nullptr;
	
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	
public:
	AEnemiesSpawner();
};
