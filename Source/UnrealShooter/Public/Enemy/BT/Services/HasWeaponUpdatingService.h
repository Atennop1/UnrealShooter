// Copyright Atennop. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Enemy/BT/Services/BTServiceWithTick.h"
#include "HasWeaponUpdatingService.generated.h"

UCLASS()
class UNREALSHOOTER_API UHasWeaponUpdatingService : public UBTServiceWithTick
{
	GENERATED_BODY()

private:
	UPROPERTY(EditInstanceOnly)
	FBlackboardKeySelector HasWeaponKey;

	virtual void ReceiveTick(UBehaviorTreeComponent& OwnerComp) override;

public:
	UHasWeaponUpdatingService();
};
