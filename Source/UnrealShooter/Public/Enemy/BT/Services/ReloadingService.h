// Copyright Atennop. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BTServiceWithTick.h"
#include "BehaviorTree/BTService.h"
#include "ReloadingService.generated.h"

UCLASS()
class UNREALSHOOTER_API UReloadingService : public UBTServiceWithTick
{
	GENERATED_BODY()

private:
	virtual void ReceiveTick(UBehaviorTreeComponent& OwnerComp) override;

public:
	UReloadingService();
};
