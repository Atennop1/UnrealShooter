// Copyright Atennop. All Rights Reserved.

#include "Enemy/BT/Decorators/CanPatrolDecorator.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UCanPatrolDecorator::UCanPatrolDecorator()
{
	NodeName = TEXT("CanPatrol");
	CanSeePlayer.AddBoolFilter(this, GET_MEMBER_NAME_CHECKED(UCanPatrolDecorator, CanSeePlayer));
	HasWeapon.AddBoolFilter(this, GET_MEMBER_NAME_CHECKED(UCanPatrolDecorator, HasWeapon));
}

bool UCanPatrolDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	const UBlackboardComponent *BlackboardComponent = OwnerComp.GetAIOwner()->GetBlackboardComponent();
	return !BlackboardComponent->GetValueAsBool(CanSeePlayer.SelectedKeyName) || !BlackboardComponent->GetValueAsBool(HasWeapon.SelectedKeyName);
}

