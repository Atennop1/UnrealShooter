// Copyright Atennop and Krypton. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "HealthUpdatingService.generated.h"

UCLASS()
class UNREALSHOOTER_API UHealthUpdatingService : public UBTService
{
	GENERATED_BODY()

private:
	UPROPERTY(EditInstanceOnly)
	FBlackboardKeySelector HealthKey;
	
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

public:
	UHealthUpdatingService();
};
