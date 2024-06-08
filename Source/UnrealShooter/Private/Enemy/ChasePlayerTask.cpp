// Copyright Atennop and Krypton. All Rights Reserved.

#include "Enemy/ChasePlayerTask.h"

EBTNodeResult::Type UChasePlayerTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	
	
	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}

UChasePlayerTask::UChasePlayerTask()
{
	NodeName = TEXT("Chase Player");
}
