// Copyright Atennop and Krypton. All Rights Reserved.

#include "Enemy/BT/JumpingService.h"
#include "AIController.h"
#include "Enemy/EnemyCharacter.h"
#include "Kismet/KismetMathLibrary.h"

UJumpingService::UJumpingService()
{
	NodeName = TEXT("Jumping Service");
}

void UJumpingService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	const AEnemyCharacter *Enemy = Cast<AEnemyCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	
	if (UKismetMathLibrary::RandomBool())
		Enemy->GetJumpingComponent()->StartJumping();
}
