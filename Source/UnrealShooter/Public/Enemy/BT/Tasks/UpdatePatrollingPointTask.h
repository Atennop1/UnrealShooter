// Copyright Atennop. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "UpdatePatrollingPointTask.generated.h"

UCLASS()
class UNREALSHOOTER_API UUpdatePatrollingPointTask : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

private:
	UPROPERTY(EditInstanceOnly)
	FBlackboardKeySelector PatrolPositionKey;
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

public:
	UUpdatePatrollingPointTask();
};
