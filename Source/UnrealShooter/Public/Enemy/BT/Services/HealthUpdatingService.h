// Copyright Atennop. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BTServiceWithTick.h"
#include "BehaviorTree/BTService.h"
#include "HealthUpdatingService.generated.h"

UCLASS()
class UNREALSHOOTER_API UHealthUpdatingService : public UBTServiceWithTick
{
	GENERATED_BODY()

private:
	UPROPERTY(EditInstanceOnly)
	FBlackboardKeySelector HealthKey;

	virtual void ReceiveTick(UBehaviorTreeComponent& OwnerComp) override;

public:
	UHealthUpdatingService();
};
