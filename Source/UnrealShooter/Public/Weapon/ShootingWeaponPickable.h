// Copyright Atennop and Krypton. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
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
	FFirearmState State;
	
public:
	AShootingWeaponPickable();
	virtual FFirearmState GetState() override;
	virtual void SetState(const FFirearmState NewState) override;
};
