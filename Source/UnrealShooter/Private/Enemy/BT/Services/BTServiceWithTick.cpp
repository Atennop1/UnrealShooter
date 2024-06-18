// Copyright Atennop. All Rights Reserved.

#include "Enemy/BT/Services/BTServiceWithTick.h"

void UBTServiceWithTick::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	TimeSinceLastTick += DeltaSeconds;

	if (TimeSinceLastTick >= Interval)
	{
		TimeSinceLastTick = FMath::FRandRange(-RandomDeviation, RandomDeviation);
		ReceiveTick(OwnerComp);
	}
}
