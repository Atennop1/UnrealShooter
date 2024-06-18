// Copyright Atennop. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "Runtime/AIModule/Classes/AIController.h"
#include "EnemyController.generated.h"

UCLASS()
class UNREALSHOOTER_API AEnemyController : public AAIController
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly, meta=(AllowPrivateAccess))
	UBehaviorTree *BehaviorTree = nullptr;
	
protected:
	virtual void BeginPlay() override;

public:
	AEnemyController();
};
