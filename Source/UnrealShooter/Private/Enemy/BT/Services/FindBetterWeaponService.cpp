// Copyright Atennop and Krypton. All Rights Reserved.

#include "Enemy/BT/Services/FindBetterWeaponService.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Enemy/EnemyCharacter.h"
#include "EnvironmentQuery/EnvQueryManager.h"
#include "Weapon/IFirearm.h"
#include "Weapon/Pickables/IFirearmPickable.h"

UFindBetterWeaponService::UFindBetterWeaponService()
{
	NodeName = TEXT("Find Better Weapon");
	BetterWeaponPickableSelector.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(UFindBetterWeaponService, BetterWeaponPickableSelector), AActor::StaticClass());
}

void UFindBetterWeaponService::ReceiveTick(UBehaviorTreeComponent& OwnerComp)
{
	OwnerComp.GetAIOwner()->GetBlackboardComponent()->SetValueAsObject(BetterWeaponPickableSelector.SelectedKeyName, nullptr);
	FEnvQueryRequest QueryRequest = FEnvQueryRequest(FindingQuery, OwnerComp.GetAIOwner()->GetPawn());
	QueryRequest.Execute(EEnvQueryRunMode::AllMatching, this, &UFindBetterWeaponService::OnFindingQueryFinished);
}

// ReSharper disable once CppPassValueParameterByConstReference
void UFindBetterWeaponService::OnFindingQueryFinished(TSharedPtr<FEnvQueryResult> Result) const
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
		Cast<AAIController>(Cast<AEnemyCharacter>(Result->Owner)->GetController())->GetBlackboardComponent()->SetValueAsObject(BetterWeaponPickableSelector.SelectedKeyName, Cast<AActor>(BestPickable));
	}
}
