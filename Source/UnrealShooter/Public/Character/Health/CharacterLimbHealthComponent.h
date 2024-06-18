// Copyright Atennop. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CharacterHealthComponent.h"
#include "IHealth.h"
#include "Components/CapsuleComponent.h"
#include "Components/SceneComponent.h"
#include "CharacterLimbHealthComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class UNREALSHOOTER_API UCharacterLimbHealthComponent : public UCapsuleComponent, public IHealth
{
	GENERATED_BODY()

private:
	UPROPERTY()
	UCharacterHealthComponent *HealthComponent = nullptr;

	UPROPERTY(EditDefaultsOnly)
	float DamageMultiplier = 1;
	
protected:
	virtual void BeginPlay() override;

public:
	UCharacterLimbHealthComponent();

	virtual int GetCurrentHealth() override { return HealthComponent->GetCurrentHealth(); }
	virtual int GetMaxHealth() override { return HealthComponent->GetMaxHealth(); }
	virtual bool IsDead() override { return HealthComponent->IsDead(); }
	
	virtual void Heal(int HealingHealth) override { HealthComponent->Heal(HealingHealth); }
	virtual void Damage(int DamagingHealth) override;
};
