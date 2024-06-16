// Copyright Atennop and Krypton. All Rights Reserved.

#include "Enemy/BT/Tasks/FindAmmoTask.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Enemy/EnemyCharacter.h"
#include "EnvironmentQuery/EnvQueryManager.h"
#include "Weapon/IFirearm.h"
#include "Weapon/Pickables/IAmmoPickable.h"

UFindAmmoTask::UFindAmmoTask()
{
	NodeName = TEXT("Find Ammo");
	BlackboardKey.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(UFindAmmoTask, BlackboardKey), AActor::StaticClass());
}

EBTNodeResult::Type UFindAmmoTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	OwnerComp.GetAIOwner()->GetBlackboardComponent()->SetValueAsObject(BlackboardKey.SelectedKeyName, nullptr);
	FEnvQueryRequest QueryRequest = FEnvQueryRequest(FindingQuery, OwnerComp.GetAIOwner()->GetPawn());
	
	QueryRequest.Execute(EEnvQueryRunMode::AllMatching, this, &UFindAmmoTask::OnFindingQueryFinished);
	return EBTNodeResult::Succeeded;
}

// ReSharper disable once CppPassValueParameterByConstReference
void UFindAmmoTask::OnFindingQueryFinished(TSharedPtr<FEnvQueryResult> Result) const
{
	if (!Result->IsSuccessful())
		return;

	const AEnemyCharacter *Enemy = Cast<AEnemyCharacter>(Result->Owner);
	IFirearm *CurrentFirearm = Cast<IFirearm>(&*Enemy->GetWeaponHoldingComponent()->GetHoldingWeapon());

	TArray<AActor*> Pickables;
	Result->GetAllAsActors(Pickables);
	IAmmoPickable* BestPickable = nullptr;
	
	for (const auto PickableActor : Pickables)
		if (IAmmoPickable *Pickable = Cast<IAmmoPickable>(PickableActor); CurrentFirearm != nullptr && Pickable != nullptr && Pickable->GetAmmoType() == CurrentFirearm->GetWeaponType())
			BestPickable = Pickable;

	Cast<AAIController>(Cast<AEnemyCharacter>(Result->Owner)->GetController())->GetBlackboardComponent()->SetValueAsObject(BlackboardKey.SelectedKeyName, Cast<AActor>(BestPickable));
}
