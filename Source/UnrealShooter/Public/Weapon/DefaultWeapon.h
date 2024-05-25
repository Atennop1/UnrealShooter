// Copyright Atennop and Krypton. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "IWeapon.h"
#include "GameFramework/Actor.h"
#include "DefaultWeapon.generated.h"

UCLASS()
class UNREALSHOOTER_API ADefaultWeapon : public AActor, public IWeapon
{
	GENERATED_BODY()

public:
	// WORK IN PROGRESS
	
	ADefaultWeapon();
	EWeaponType GetWeaponType() override { return EWeaponType::Rifle; }

	void Shoot(FVector Direction) override { } 
	void Reload() override { }
};
