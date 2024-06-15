// Copyright Atennop and Krypton. All Rights Reserved.

#include "Enemy/BT/Services/JumpingService.h"
#include "AIController.h"
#include "Enemy/EnemyCharacter.h"
#include "Kismet/KismetMathLibrary.h"

UJumpingService::UJumpingService()
{
	NodeName = TEXT("Jumping Service");
}

void UJumpingService::ReceiveTick(UBehaviorTreeComponent& OwnerComp)
{
	if (AEnemyCharacter* Enemy = Cast<AEnemyCharacter>(OwnerComp.GetAIOwner()->GetPawn()); Enemy != nullptr && UKismetMathLibrary::RandomBool())
	{
		Enemy->GetJumpingComponent()->StartJumping();
		GetWorld()->GetTimerManager().SetTimer(StopJumpingTimerHandle, [Enemy] { if (Enemy != nullptr) Enemy->StopJumping(); }, 0.3f, false);
	}
}
