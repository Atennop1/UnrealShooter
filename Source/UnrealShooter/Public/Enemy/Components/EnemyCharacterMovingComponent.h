// Copyright Atennop and Krypton. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Character/Movement/ICharacterMovingComponent.h"
#include "Components/ActorComponent.h"
#include "EnemyCharacterMovingComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class UNREALSHOOTER_API UEnemyCharacterMovingComponent : public UActorComponent, public ICharacterMovingComponent
{
	GENERATED_BODY()

public:
	UEnemyCharacterMovingComponent();
	virtual void Move(const FVector2D Input) override;
};
