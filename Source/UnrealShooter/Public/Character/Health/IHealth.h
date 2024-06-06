// Copyright Atennop and Krypton. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IHealth.generated.h"

UINTERFACE(MinimalAPI)
class UHealth : public UInterface
{
	GENERATED_BODY()
};

class UNREALSHOOTER_API IHealth
{
	GENERATED_BODY()

public:
	virtual int GetCurrentHealth() = 0;
	virtual int GetMaxHealth() = 0;
	virtual bool IsDead() = 0;
	
	virtual void Heal(int HealingHealth) = 0;
	virtual void Damage(int Health) = 0;
};
