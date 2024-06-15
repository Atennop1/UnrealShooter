// Copyright Atennop and Krypton. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BTServiceWithTick.h"
#include "BehaviorTree/BTService.h"
#include "JumpingService.generated.h"

UCLASS()
class UNREALSHOOTER_API UJumpingService : public UBTServiceWithTick
{
	GENERATED_BODY()

private:
	FTimerHandle StopJumpingTimerHandle;

	virtual void ReceiveTick(UBehaviorTreeComponent& OwnerComp) override;

public:
	UJumpingService();
};
