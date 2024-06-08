// Copyright Atennop and Krypton. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Weapon/Interfaces/IWeapon.h"
#include "CharacterWeaponHoldingComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class UNREALSHOOTER_API UCharacterWeaponHoldingComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	UPROPERTY()
	class AShooterCharacter *Character = nullptr;

	UPROPERTY(EditDefaultsOnly)
	TMap<UClass*, FName> WeaponsToSockets;
	
	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess))
	bool IsHoldingWeapon = false;

	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess))
	TScriptInterface<IWeapon> HoldingWeapon = nullptr;

protected:
	virtual void BeginPlay() override;
	
public: 
	UCharacterWeaponHoldingComponent();
	
	TScriptInterface<IWeapon> GetHoldingWeapon() const { return HoldingWeapon; }
	bool GetIsHolding() const { return IsHoldingWeapon; }
	
	void Hold(TScriptInterface<IWeapon> Weapon);
	void Unhold();
};
