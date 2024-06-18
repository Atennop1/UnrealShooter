// Copyright Atennop. All Rights Reserved.

#include "Enemy/BT/Services/FindHealthService.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Character/Health/HealthPickable.h"
#include "Enemy/EnemyCharacter.h"
#include "EnvironmentQuery/EnvQueryManager.h"

UFindHealthService::UFindHealthService()
{
	NodeName = TEXT("Find Health");
	HealthPickableSelector.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(UFindHealthService, HealthPickableSelector), AActor::StaticClass());
}

void UFindHealthService::ReceiveTick(UBehaviorTreeComponent& OwnerComp)
{
	OwnerComp.GetAIOwner()->GetBlackboardComponent()->SetValueAsObject(HealthPickableSelector.SelectedKeyName, nullptr);
	FEnvQueryRequest QueryRequest = FEnvQueryRequest(FindingQuery, OwnerComp.GetAIOwner()->GetPawn());
	QueryRequest.Execute(EEnvQueryRunMode::AllMatching, this, &UFindHealthService::OnFindingQueryFinished);
}

// ReSharper disable once CppPassValueParameterByConstReference
void UFindHealthService::OnFindingQueryFinished(TSharedPtr<FEnvQueryResult> Result) const
{
	if (!Result->IsSuccessful())
		return;

	TArray<AActor*> Pickables;
	Result->GetAllAsActors(Pickables);
	AHealthPickable* BestPickable = nullptr;
	
	for (const auto PickableActor : Pickables)
		if (AHealthPickable *Pickable = Cast<AHealthPickable>(PickableActor); Pickable != nullptr && (BestPickable == nullptr || BestPickable->GetHealthToAdd() < Pickable->GetHealthToAdd()))
			BestPickable = Pickable;

	Cast<AAIController>(Cast<AEnemyCharacter>(Result->Owner)->GetController())->GetBlackboardComponent()->SetValueAsObject(HealthPickableSelector.SelectedKeyName, Cast<AActor>(BestPickable));
}
