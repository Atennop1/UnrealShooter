// Copyright Atennop and Krypton. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "ShootingService.generated.h"

UCLASS()
class UNREALSHOOTER_API UShootingService : public UBTService
{
	GENERATED_BODY()

private:
	UPROPERTY(EditInstanceOnly)
	int CheckSphereRadius = 40;
	
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

public:
	UShootingService();
};
