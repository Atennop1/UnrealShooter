// Copyright Atennop and Krypton. All Rights Reserved.

#include "Enemy/Components/EnemyCharacterPatrollingComponent.h"

UEnemyCharacterPatrollingComponent::UEnemyCharacterPatrollingComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UEnemyCharacterPatrollingComponent::BeginPlay()
{
	Super::BeginPlay();
	if (!IsValid(SplineActor))
		return;
	
	Spline = SplineActor->GetComponentByClass<USplineComponent>();
	if (IsValid(Spline))
		PointIndex = FMath::RandRange(0, Spline->GetNumberOfSplinePoints() - 1);
}

void UEnemyCharacterPatrollingComponent::Init(USplineComponent* NewSpline)
{
	Spline = NewSpline;
	check(IsValid(Spline))
	PointIndex = FMath::RandRange(0, Spline->GetNumberOfSplinePoints() - 1);
}

FVector UEnemyCharacterPatrollingComponent::GetNextPatrollingPoint()
{
	PointIndex++;
	
	if (PointIndex == Spline->GetNumberOfSplinePoints())
		PointIndex = 0;

	return Spline->GetLocationAtSplinePoint(PointIndex, ESplineCoordinateSpace::World);
}