// Copyright Atennop. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HealthPickable.generated.h"

UCLASS()
class UNREALSHOOTER_API AHealthPickable : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly)
	int HealthToAdd;
	
public:
	AHealthPickable();
	int GetHealthToAdd() const { return HealthToAdd; } 
};
