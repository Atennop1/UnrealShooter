// Copyright Atennop and Krypton. All Rights Reserved.

#include "Enemy/BT/Tasks/FindBetterWeaponTask.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Enemy/EnemyCharacter.h"
#include "EnvironmentQuery/EnvQueryManager.h"
#include "Weapon/Interfaces/IFirearm.h"
#include "Weapon/Interfaces/IFirearmPickable.h"

UFindBetterWeaponTask::UFindBetterWeaponTask()
{
	NodeName = TEXT("Find Better Weapon");
	BlackboardKey.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(UFindBetterWeaponTask, BlackboardKey), AActor::StaticClass());
}

EBTNodeResult::Type UFindBetterWeaponTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	OwnerComp.GetAIOwner()->GetBlackboardComponent()->SetValueAsObject(BlackboardKey.SelectedKeyName, nullptr);
	FEnvQueryRequest QueryRequest = FEnvQueryRequest(FindingQuery, OwnerComp.GetAIOwner());
	
	QueryRequest.Execute(EEnvQueryRunMode::AllMatching, this, &UFindBetterWeaponTask::OnFindingQueryFinished);
	return EBTNodeResult::Succeeded;
}

// ReSharper disable once CppPassValueParameterByConstReference
void UFindBetterWeaponTask::OnFindingQueryFinished(TSharedPtr<FEnvQueryResult> Result) const
{
	if (!Result->IsSuccsessful())
		return;

	const AEnemyCharacter *Enemy = Cast<AEnemyCharacter>(Cast<AAIController>(Result->Owner)->GetPawn());
	IFirearm *CurrentFirearm = Cast<IFirearm>(&*Enemy->GetWeaponHoldingComponent()->GetHoldingWeapon());

	TArray<AActor*> Pickables;
	Result->GetAllAsActors(Pickables);
	int BestPriority = Enemy->GetWeaponHoldingComponent()->GetIsHolding() ? CurrentFirearm->GetData().Priority : -1;
	IFirearmPickable* BestPickable = nullptr;

	for (const auto PickableActor : Pickables)
	{
		if (IFirearmPickable *Pickable = Cast<IFirearmPickable>(PickableActor); PickableActor != nullptr && BestPriority < Pickable->GetPriority())
		{
			BestPickable = Pickable;
			BestPriority = BestPickable->GetPriority();
		}
	}

	if (BestPriority > (Enemy->GetWeaponHoldingComponent()->GetIsHolding() ? CurrentFirearm->GetData().Priority : -1))
		Cast<AAIController>(Result->Owner)->GetBlackboardComponent()->SetValueAsObject(BlackboardKey.SelectedKeyName, Cast<AActor>(BestPickable));
}

