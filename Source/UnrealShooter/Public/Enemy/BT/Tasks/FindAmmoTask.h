// Copyright Atennop and Krypton. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "EnvironmentQuery/EnvQuery.h"
#include "FindAmmoTask.generated.h"

UCLASS()
class UNREALSHOOTER_API UFindAmmoTask : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

private:
	UPROPERTY(EditInstanceOnly)
	UEnvQuery* FindingQuery = nullptr;

	void OnFindingQueryFinished(TSharedPtr<FEnvQueryResult> Result) const;
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

public:
	UFindAmmoTask();
};
