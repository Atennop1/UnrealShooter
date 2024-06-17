// Copyright Atennop and Krypton. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/SplineComponent.h"
#include "EnemyCharacterPatrollingComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class UNREALSHOOTER_API UEnemyCharacterPatrollingComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	UPROPERTY(EditInstanceOnly)
	AActor *SplineActor = nullptr;

	UPROPERTY()
	USplineComponent *Spline = nullptr;
	int PointIndex = 0;

protected:
	virtual void BeginPlay() override;

public:
	UEnemyCharacterPatrollingComponent();

	void Init(USplineComponent *NewSpline);
	FVector GetNextPatrollingPoint();
};
