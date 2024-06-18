// Copyright Atennop. All Rights Reserved.

#include "Enemy/BT/Services/HealthUpdatingService.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Enemy/EnemyCharacter.h"

UHealthUpdatingService::UHealthUpdatingService()
{
	NodeName = TEXT("Health Updating Service");
	HealthKey.AddFloatFilter(this, GET_MEMBER_NAME_CHECKED(UHealthUpdatingService, HealthKey));
}

void UHealthUpdatingService::ReceiveTick(UBehaviorTreeComponent& OwnerComp)
{
	const AEnemyCharacter *Enemy = Cast<AEnemyCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	OwnerComp.GetAIOwner()->GetBlackboardComponent()->SetValueAsFloat(HealthKey.SelectedKeyName, (float)Enemy->GetHealthComponent()->GetCurrentHealth() / (float)Enemy->GetHealthComponent()->GetMaxHealth());
}
