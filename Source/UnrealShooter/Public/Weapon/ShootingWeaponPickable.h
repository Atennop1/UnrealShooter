// Copyright Atennop and Krypton. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Data/FirearmData.h"
#include "Data/FirearmState.h"
#include "GameFramework/Actor.h"
#include "Interfaces/IFirearmPickable.h"
#include "ShootingWeaponPickable.generated.h"

UCLASS()
class UNREALSHOOTER_API AShootingWeaponPickable : public AActor, public IFirearmPickable
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly)
	int Priority = 0;
	
	UPROPERTY(EditDefaultsOnly)
	FFirearmState State;

	
public:
	AShootingWeaponPickable();
	
	virtual FFirearmState GetState() override { return State; }
	virtual void SetState(const FFirearmState NewState) override { State = NewState; }

	virtual int GetPriority() override { return Priority; }
};
