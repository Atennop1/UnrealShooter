// Copyright Atennop and Krypton. All Rights Reserved.

#include "Enemy/BT/HealthUpdatingService.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Character/ShooterCharacter.h"

UHealthUpdatingService::UHealthUpdatingService()
{
	NodeName = TEXT("Health Updating Service");
	HealthKey.AddFloatFilter(this, GET_MEMBER_NAME_CHECKED(UHealthUpdatingService, HealthKey));
}

void UHealthUpdatingService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	const AShooterCharacter *Enemy = Cast<AShooterCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	OwnerComp.GetAIOwner()->GetBlackboardComponent()->SetValueAsFloat(HealthKey.SelectedKeyName, (float)Enemy->GetHealthComponent()->GetCurrentHealth() / (float)Enemy->GetHealthComponent()->GetMaxHealth());
}
