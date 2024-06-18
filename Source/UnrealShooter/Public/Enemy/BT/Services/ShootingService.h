// Copyright Atennop. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BTServiceWithTick.h"
#include "BehaviorTree/BTService.h"
#include "ShootingService.generated.h"

UCLASS()
class UNREALSHOOTER_API UShootingService : public UBTServiceWithTick
{
	GENERATED_BODY()

private:
	virtual void ReceiveTick(UBehaviorTreeComponent& OwnerComp) override;

public:
	UShootingService();
};
