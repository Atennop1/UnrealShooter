// Copyright Atennop and Krypton. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "IHealth.h"
#include "Components/ActorComponent.h"
#include "CharacterHealthComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class UNREALSHOOTER_API UCharacterHealthComponent : public UActorComponent, public IHealth
{
	GENERATED_BODY()

private:
	UPROPERTY()
	ACharacter *Character = nullptr;

	UPROPERTY(BlueprintReadWrite, meta=(AllowPrivateAccess))
	USceneComponent *ComponentToAttachCamera = nullptr;
	
	UPROPERTY(EditDefaultsOnly)
	int MaxHealth = 100;
	int CurrentHealth = 100;

	UPROPERTY(EditDefaultsOnly)
	FTransform CameraTransformAfterDeath;

	void Die() const;

protected:
	virtual void BeginPlay() override;

public:
	UCharacterHealthComponent();

	virtual int GetCurrentHealth() override { return CurrentHealth; }
	virtual int GetMaxHealth() override { return MaxHealth; }
	virtual bool IsDead() override { return CurrentHealth <= 0; }
	
	virtual void Heal(int HealingHealth) override;
	virtual void Damage(int DamagingHealth) override;
};
