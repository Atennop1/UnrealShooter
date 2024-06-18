// Copyright Atennop. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PickablesSpawner.generated.h"

UCLASS()
class UNREALSHOOTER_API APickablesSpawner : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere)
	float TimeForSpawn = 20;
	float ElapsedTime = 0;
	
	UPROPERTY(EditAnywhere)
	float StartDelay = 5;

	UPROPERTY(EditAnywhere)
	float SphereTraceRadius = 20;
	
	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<AActor>> PickablesToSpawn;

	UPROPERTY()
	AActor *LastSpawnedPickable = nullptr;
	
protected:
	virtual void Tick(float DeltaTime) override;
	
public:
	APickablesSpawner();
};
