// Copyright Atennop and Krypton. All Rights Reserved.

#include "Enemy/BT/Tasks/UpdatePatrollingPointTask.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Enemy/EnemyCharacter.h"

UUpdatePatrollingPointTask::UUpdatePatrollingPointTask()
{
	NodeName = TEXT("Update Patrolling Point");
	PatrolPositionKey.AddVectorFilter(this, GET_MEMBER_NAME_CHECKED(UUpdatePatrollingPointTask, PatrolPositionKey));
}

EBTNodeResult::Type UUpdatePatrollingPointTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const AEnemyCharacter *Enemy = Cast<AEnemyCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	OwnerComp.GetAIOwner()->GetBlackboardComponent()->SetValueAsVector(PatrolPositionKey.SelectedKeyName, Enemy->GetPatrollingComponent()->GetNextPatrollingPoint());
	
	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}