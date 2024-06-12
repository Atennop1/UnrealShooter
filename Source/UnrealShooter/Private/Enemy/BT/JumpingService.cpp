// Copyright Atennop and Krypton. All Rights Reserved.

#include "Enemy/BT/JumpingService.h"

#include "AIController.h"
#include "Character/ShooterCharacter.h"
#include "Kismet/KismetMathLibrary.h"

UJumpingService::UJumpingService()
{
	NodeName = TEXT("Jumping Service");
}

void UJumpingService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	const AShooterCharacter *Enemy = Cast<AShooterCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	
	if (UKismetMathLibrary::RandomBool())
		Enemy->GetJumpingComponent()->StartJumping();
}
