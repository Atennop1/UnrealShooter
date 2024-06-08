// Copyright Atennop and Krypton. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "LookAtPlayerTask.generated.h"

UCLASS()
class UNREALSHOOTER_API ULookAtPlayerTask : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

private:
	UPROPERTY(EditInstanceOnly, meta=(AllowPrivateAccess))
	float SearchRadius = 200;
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

public:
	ULookAtPlayerTask();
};
