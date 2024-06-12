// Copyright Atennop and Krypton. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Character/Movement/ICharacterJumpingComponent.h"
#include "Components/ActorComponent.h"
#include "EnemyCharacterJumpingComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class UNREALSHOOTER_API UEnemyCharacterJumpingComponent : public UActorComponent, public ICharacterJumpingComponent
{
	GENERATED_BODY()

public:
	UEnemyCharacterJumpingComponent();

	virtual void StartJumping() override;
	virtual void StopJumping() override;
};
