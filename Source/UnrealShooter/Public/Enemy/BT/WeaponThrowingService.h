// Copyright Atennop and Krypton. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "WeaponThrowingService.generated.h"

UCLASS()
class UNREALSHOOTER_API UWeaponThrowingService : public UBTService
{
	GENERATED_BODY()

private:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

public:
	UWeaponThrowingService();
};
