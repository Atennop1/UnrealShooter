// Copyright Atennop. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Character/ShooterCharacter.h"
#include "Components/EnemyCharacterPatrollingComponent.h"
#include "EnemyCharacter.generated.h"

UCLASS()
class UNREALSHOOTER_API AEnemyCharacter : public AShooterCharacter
{
	GENERATED_BODY()

private:
	UPROPERTY(BlueprintReadWrite, meta=(AllowPrivateAccess=true))
	UEnemyCharacterPatrollingComponent *PatrollingComponent = nullptr;

protected:
	virtual void BeginPlay() override;
	
public:
	AEnemyCharacter();

	UEnemyCharacterPatrollingComponent *GetPatrollingComponent() const { return PatrollingComponent; }
};
