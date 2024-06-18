// Copyright Atennop. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTServiceWithTick.generated.h"

UCLASS()
class UNREALSHOOTER_API UBTServiceWithTick : public UBTService
{
	GENERATED_BODY()

private:
	float TimeSinceLastTick = 0.0f;
	
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
protected:
	virtual void ReceiveTick(UBehaviorTreeComponent& OwnerComp) { };
};
