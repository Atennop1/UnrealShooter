// Copyright Atennop and Krypton. All Rights Reserved.

#include "AIController.h"
#include "Enemy/Tasks/FocusTask.h"
#include "BehaviorTree/BlackboardComponent.h"

UFocusTask::UFocusTask()
{
	NodeName = TEXT("Focus On Object");
	BlackboardKey.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(UFocusTask, BlackboardKey), AActor::StaticClass());
}

EBTNodeResult::Type UFocusTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController *AIController = OwnerComp.GetAIOwner();
	AIController->SetFocus(Cast<AActor>(AIController->GetBlackboardComponent()->GetValueAsObject(BlackboardKey.SelectedKeyName)));
	
	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}
