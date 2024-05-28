// Copyright Atennop and Krypton. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CharacterWeaponThrowingComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class UNREALSHOOTER_API UCharacterWeaponThrowingComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	UPROPERTY()
	class AShooterCharacter *Character = nullptr;

	UPROPERTY(EditDefaultsOnly)
	float DefaultThrowingForce = 50000;

	UPROPERTY(EditDefaultsOnly)
	float StartDistance = 50;
	
	UPROPERTY(EditDefaultsOnly)
	TMap<UClass*, UClass*> WeaponsToPickables;

protected:
	virtual void BeginPlay() override;

public:
	UCharacterWeaponThrowingComponent();
	void Throw();
};
