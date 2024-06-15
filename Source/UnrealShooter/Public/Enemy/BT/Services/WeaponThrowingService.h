// Copyright Atennop and Krypton. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BTServiceWithTick.h"
#include "BehaviorTree/BTService.h"
#include "WeaponThrowingService.generated.h"

UCLASS()
class UNREALSHOOTER_API UWeaponThrowingService : public UBTServiceWithTick
{
	GENERATED_BODY()

private:
	virtual void ReceiveTick(UBehaviorTreeComponent& OwnerComp) override;

public:
	UWeaponThrowingService();
};
