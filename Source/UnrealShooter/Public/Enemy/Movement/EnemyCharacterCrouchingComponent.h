// Copyright Atennop and Krypton. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Character/Movement/ICharacterCrouchingComponent.h"
#include "Components/ActorComponent.h"
#include "EnemyCharacterCrouchingComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class UNREALSHOOTER_API UEnemyCharacterCrouchingComponent : public UActorComponent, public ICharacterCrouchingComponent
{
	GENERATED_BODY()

public:
	UEnemyCharacterCrouchingComponent();
	virtual bool GetIsCrouching() override;
	
	virtual void StartCrouching() override;
	virtual void StopCrouching() override;
};
