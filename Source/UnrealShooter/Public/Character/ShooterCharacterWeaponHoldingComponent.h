// Copyright Atennop and Krypton. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Weapon/IWeapon.h"
#include "ShooterCharacterWeaponHoldingComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class UNREALSHOOTER_API UShooterCharacterWeaponHoldingComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess))
	bool IsHoldingWeapon = false;

	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess))
	bool IsAiming = false;

	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess))
	TScriptInterface<IWeapon> HoldingWeapon = nullptr;

public: 
	UShooterCharacterWeaponHoldingComponent();
	IWeapon *GetHoldingWeapon() const { return Cast<IWeapon>(HoldingWeapon.GetObject()); }
	
	void Hold(const IWeapon *Weapon);
	void Unhold();

	void StartAim();
	void StopAim();
};
