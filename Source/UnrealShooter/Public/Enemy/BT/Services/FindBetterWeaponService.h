// Copyright Atennop. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BTServiceWithTick.h"
#include "EnvironmentQuery/EnvQuery.h"
#include "FindBetterWeaponService.generated.h"

UCLASS()
class UNREALSHOOTER_API UFindBetterWeaponService : public UBTServiceWithTick
{
	GENERATED_BODY()

private:
	UPROPERTY(EditInstanceOnly)
	FBlackboardKeySelector BetterWeaponPickableSelector;
	
	UPROPERTY(EditInstanceOnly)
	UEnvQuery* FindingQuery = nullptr;

	void OnFindingQueryFinished(TSharedPtr<FEnvQueryResult> Result) const;
	virtual void ReceiveTick(UBehaviorTreeComponent& OwnerComp) override;

public:
	UFindBetterWeaponService();
};
