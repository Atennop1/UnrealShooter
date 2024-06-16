// Copyright Atennop and Krypton. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "IWeaponPickable.h"
#include "UObject/Interface.h"
#include "Weapon/Data/FirearmState.h"
#include "IFirearmPickable.generated.h"

UINTERFACE(MinimalAPI)
class UFirearmPickable : public UWeaponPickable
{
	GENERATED_BODY()
};

class UNREALSHOOTER_API IFirearmPickable : public IWeaponPickable
{
	GENERATED_BODY()

public:
	virtual int GetPriority() = 0;
	
	virtual FFirearmState GetState() = 0;
	virtual void SetState(FFirearmState State) = 0;
};
