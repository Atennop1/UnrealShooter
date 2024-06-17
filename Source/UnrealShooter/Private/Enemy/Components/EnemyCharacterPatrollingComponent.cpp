// Copyright Atennop and Krypton. All Rights Reserved.

#include "Enemy/Components/EnemyCharacterPatrollingComponent.h"

UEnemyCharacterPatrollingComponent::UEnemyCharacterPatrollingComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UEnemyCharacterPatrollingComponent::BeginPlay()
{
	Super::BeginPlay();
	Spline = SplineActor->GetComponentByClass<USplineComponent>();
}

void UEnemyCharacterPatrollingComponent::Init(USplineComponent* NewSpline)
{
	Spline = NewSpline;
	check(IsValid(Spline))
}

FVector UEnemyCharacterPatrollingComponent::GetNextPatrollingPoint()
{
	PointIndex++;
	
	if (PointIndex == Spline->GetNumberOfSplinePoints())
		PointIndex = 0;

	return Spline->GetLocationAtSplinePoint(PointIndex, ESplineCoordinateSpace::World);
}