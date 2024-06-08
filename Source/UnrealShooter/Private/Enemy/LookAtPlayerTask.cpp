// Copyright Atennop and Krypton. All Rights Reserved.

#include "Enemy/LookAtPlayerTask.h"
#include "AIController.h"
#include "Character/ShooterCharacter.h"
#include "Kismet/GameplayStatics.h"

ULookAtPlayerTask::ULookAtPlayerTask()
{
	NodeName = TEXT("Look At Player");
}

EBTNodeResult::Type ULookAtPlayerTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const ACharacter *Enemy = Cast<ACharacter>(OwnerComp.GetAIOwner()->GetPawn());
	const AShooterCharacter *Player = Cast<AShooterCharacter>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPawn());

	if (const float Distance = Enemy->GetDistanceTo(Player); !IsValid(Enemy) || !IsValid(Player) || Distance > SearchRadius)
	{
		OwnerComp.GetAIOwner()->ClearFocus(EAIFocusPriority::Gameplay);
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return EBTNodeResult::Failed;
	}

	OwnerComp.GetAIOwner()->SetFocus(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPawn());
	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}
