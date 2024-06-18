// Copyright Atennop and Krypton. All Rights Reserved.

#include "Enemy/BT/Services/FindAmmoService.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Enemy/EnemyCharacter.h"
#include "EnvironmentQuery/EnvQueryManager.h"
#include "Weapon/IFirearm.h"
#include "Weapon/Pickables/IAmmoPickable.h"

UFindAmmoService::UFindAmmoService()
{
	NodeName = TEXT("Find Ammo");
	AmmoPickableSelector.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(UFindAmmoService, AmmoPickableSelector), AActor::StaticClass());
}

void UFindAmmoService::ReceiveTick(UBehaviorTreeComponent& OwnerComp)
{
	OwnerComp.GetAIOwner()->GetBlackboardComponent()->SetValueAsObject(AmmoPickableSelector.SelectedKeyName, nullptr);
	FEnvQueryRequest QueryRequest = FEnvQueryRequest(FindingQuery, OwnerComp.GetAIOwner()->GetPawn());
	QueryRequest.Execute(EEnvQueryRunMode::AllMatching, this, &UFindAmmoService::OnFindingQueryFinished);
}

// ReSharper disable once CppPassValueParameterByConstReference
void UFindAmmoService::OnFindingQueryFinished(TSharedPtr<FEnvQueryResult> Result) const
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

	Cast<AAIController>(Cast<AEnemyCharacter>(Result->Owner)->GetController())->GetBlackboardComponent()->SetValueAsObject(AmmoPickableSelector.SelectedKeyName, Cast<AActor>(BestPickable));
}
