// Copyright Atennop and Krypton. All Rights Reserved.

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
	UPROPERTY(EditInstanceOnly)
	int CheckSphereRadius = 40;

	virtual void ReceiveTick(UBehaviorTreeComponent& OwnerComp) override;

public:
	UShootingService();
};
