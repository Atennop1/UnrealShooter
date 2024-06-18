// Copyright Atennop and Krypton. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BTServiceWithTick.h"
#include "EnvironmentQuery/EnvQuery.h"
#include "FindAmmoService.generated.h"

UCLASS()
class UNREALSHOOTER_API UFindAmmoService : public UBTServiceWithTick
{
	GENERATED_BODY()

private:
	UPROPERTY(EditInstanceOnly)
	FBlackboardKeySelector AmmoPickableSelector;
	
	UPROPERTY(EditInstanceOnly)
	UEnvQuery* FindingQuery = nullptr;

	void OnFindingQueryFinished(TSharedPtr<FEnvQueryResult> Result) const;
	virtual void ReceiveTick(UBehaviorTreeComponent& OwnerComp) override;

public:
	UFindAmmoService();
};
