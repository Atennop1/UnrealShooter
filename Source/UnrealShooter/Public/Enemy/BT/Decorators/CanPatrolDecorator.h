// Copyright Atennop and Krypton. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BehaviorTree/Decorators/BTDecorator_BlackboardBase.h"
#include "BehaviorTree/Decorators/BTDecorator_BlueprintBase.h"
#include "CanPatrolDecorator.generated.h"

UCLASS()
class UNREALSHOOTER_API UCanPatrolDecorator : public UBTDecorator_BlueprintBase
{
	GENERATED_BODY()

private:
	UPROPERTY(EditInstanceOnly)
	FBlackboardKeySelector CanSeePlayer;

	UPROPERTY(EditInstanceOnly)
	FBlackboardKeySelector HasWeapon;

	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
	
public:
	UCanPatrolDecorator();
};
