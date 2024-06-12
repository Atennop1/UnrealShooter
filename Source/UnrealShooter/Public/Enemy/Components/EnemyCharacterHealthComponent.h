// Copyright Atennop and Krypton. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Character/Health/CharacterHealthComponent.h"
#include "EnemyCharacterHealthComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class UNREALSHOOTER_API UEnemyCharacterHealthComponent : public UCharacterHealthComponent
{
	GENERATED_BODY()

public:
	UEnemyCharacterHealthComponent();

	virtual void Damage(int DamagingHealth) override;
};
