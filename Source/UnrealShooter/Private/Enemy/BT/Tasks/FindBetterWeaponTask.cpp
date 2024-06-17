// Copyright Atennop and Krypton. All Rights Reserved.

#include "Enemy/BT/Tasks/FindBetterWeaponTask.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Enemy/EnemyCharacter.h"
#include "EnvironmentQuery/EnvQueryManager.h"
#include "Weapon/IFirearm.h"
#include "Weapon/Pickables/IFirearmPickable.h"

UFindBetterWeaponTask::UFindBetterWeaponTask()
{
	NodeName = TEXT("Find Better Weapon");
	BlackboardKey.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(UFindBetterWeaponTask, BlackboardKey), AActor::StaticClass());
}

EBTNodeResult::Type UFindBetterWeaponTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	OwnerComp.GetAIOwner()->GetBlackboardComponent()->SetValueAsObject(BlackboardKey.SelectedKeyName, nullptr);
	FEnvQueryRequest QueryRequest = FEnvQueryRequest(FindingQuery, OwnerComp.GetAIOwner()->GetPawn());
	
	QueryRequest.Execute(EEnvQueryRunMode::AllMatching, this, &UFindBetterWeaponTask::OnFindingQueryFinished);
	return EBTNodeResult::Succeeded;
}

// ReSharper disable once CppPassValueParameterByConstReference
void UFindBetterWeaponTask::OnFindingQueryFinished(TSharedPtr<FEnvQueryResult> Result) const
{
	if (!Result->IsSuccessful())
		return;

	const AEnemyCharacter *Enemy = Cast<AEnemyCharacter>(Result->Owner);
	IFirearm *CurrentFirearm = Cast<IFirearm>(&*Enemy->GetWeaponHoldingComponent()->GetHoldingWeapon());

	TArray<AActor*> Pickables;
	Result->GetAllAsActors(Pickables);
	IFirearmPickable* BestPickable = nullptr;
	const int CountOfItems = Pickables.Num();
	int BestPriority = Enemy->GetWeaponHoldingComponent()->GetIsHolding() ? CurrentFirearm->GetData().Priority : -1;
	
	for (int i = 0; i < CountOfItems; i++)
	{
		if (IFirearmPickable *Pickable = Cast<IFirearmPickable>(Pickables[i]); Result->GetItemScore(i) != 0 && Pickable != nullptr && BestPriority < Pickable->GetPriority())
		{
			BestPickable = Pickable;
			BestPriority = BestPickable->GetPriority();
		}
	}

	if (BestPriority > (Enemy->GetWeaponHoldingComponent()->GetIsHolding() ? CurrentFirearm->GetData().Priority : -1))
	{
		Enemy->GetWeaponThrowingComponent()->Throw();
		Cast<AAIController>(Cast<AEnemyCharacter>(Result->Owner)->GetController())->GetBlackboardComponent()->SetValueAsObject(BlackboardKey.SelectedKeyName, Cast<AActor>(BestPickable));
	}
}

