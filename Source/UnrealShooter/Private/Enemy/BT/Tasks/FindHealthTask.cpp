// Copyright Atennop and Krypton. All Rights Reserved.

#include "Enemy/BT/Tasks/FindHealthTask.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Character/Health/HealthPickable.h"
#include "Enemy/EnemyCharacter.h"
#include "EnvironmentQuery/EnvQueryManager.h"

UFindHealthTask::UFindHealthTask()
{
	NodeName = TEXT("Find Health");
	BlackboardKey.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(UFindHealthTask, BlackboardKey), AActor::StaticClass());
}

EBTNodeResult::Type UFindHealthTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	OwnerComp.GetAIOwner()->GetBlackboardComponent()->SetValueAsObject(BlackboardKey.SelectedKeyName, nullptr);
	FEnvQueryRequest QueryRequest = FEnvQueryRequest(FindingQuery, OwnerComp.GetAIOwner()->GetPawn());
	
	QueryRequest.Execute(EEnvQueryRunMode::AllMatching, this, &UFindHealthTask::OnFindingQueryFinished);
	return EBTNodeResult::Succeeded;
}

// ReSharper disable once CppPassValueParameterByConstReference
void UFindHealthTask::OnFindingQueryFinished(TSharedPtr<FEnvQueryResult> Result) const
{
	if (!Result->IsSuccessful())
		return;

	TArray<AActor*> Pickables;
	Result->GetAllAsActors(Pickables);
	AHealthPickable* BestPickable = nullptr;
	
	for (const auto PickableActor : Pickables)
		if (AHealthPickable *Pickable = Cast<AHealthPickable>(PickableActor); Pickable != nullptr && (BestPickable == nullptr || BestPickable->GetHealthToAdd() < Pickable->GetHealthToAdd()))
			BestPickable = Pickable;

	Cast<AAIController>(Cast<AEnemyCharacter>(Result->Owner)->GetController())->GetBlackboardComponent()->SetValueAsObject(BlackboardKey.SelectedKeyName, Cast<AActor>(BestPickable));
}
