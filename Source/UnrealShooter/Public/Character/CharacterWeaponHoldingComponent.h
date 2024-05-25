// Copyright Atennop and Krypton. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Weapon/IWeapon.h"
#include "CharacterWeaponHoldingComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class UNREALSHOOTER_API UCharacterWeaponHoldingComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	UPROPERTY()
	class AShooterCharacter *Character = nullptr;
	
	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess))
	bool IsHoldingWeapon = false;

	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess))
	TScriptInterface<IWeapon> HoldingWeapon = nullptr;

public: 
	UCharacterWeaponHoldingComponent();
	virtual void BeginPlay() override;
	
	IWeapon *GetHoldingWeapon() const { return Cast<IWeapon>(HoldingWeapon.GetObject()); }
	bool GetIsHoldingWeapon() const { return IsHoldingWeapon; }
	
	void Hold(const TScriptInterface<IWeapon> Weapon);
	void Unhold();
};
