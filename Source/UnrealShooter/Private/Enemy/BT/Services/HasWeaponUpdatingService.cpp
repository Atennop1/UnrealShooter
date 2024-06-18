// Copyright Atennop. All Rights Reserved.

#include "Enemy/BT/Services/HasWeaponUpdatingService.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Enemy/EnemyCharacter.h"

UHasWeaponUpdatingService::UHasWeaponUpdatingService()
{
	NodeName = TEXT("Has Weapon Updating Service");
	HasWeaponKey.AddBoolFilter(this, GET_MEMBER_NAME_CHECKED(UHasWeaponUpdatingService, HasWeaponKey));
}

void UHasWeaponUpdatingService::ReceiveTick(UBehaviorTreeComponent& OwnerComp)
{
	const AEnemyCharacter *Enemy = Cast<AEnemyCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	OwnerComp.GetAIOwner()->GetBlackboardComponent()->SetValueAsBool(HasWeaponKey.SelectedKeyName, Enemy->GetWeaponHoldingComponent()->GetIsHolding());
}
