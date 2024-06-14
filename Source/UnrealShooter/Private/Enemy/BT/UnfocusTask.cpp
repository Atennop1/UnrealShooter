// Copyright Atennop and Krypton. All Rights Reserved.

#include "Enemy/BT/UnfocusTask.h"
#include "AIController.h"

UUnfocusTask::UUnfocusTask()
{
	NodeName = TEXT("Unfocus");
}

EBTNodeResult::Type UUnfocusTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController *AIController = OwnerComp.GetAIOwner();
	AIController->ClearFocus(EAIFocusPriority::Gameplay);
	AIController->GetPawn()->bUseControllerRotationYaw = false;
	
	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}

