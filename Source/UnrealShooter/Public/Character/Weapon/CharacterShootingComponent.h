// Copyright Atennop and Krypton. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CharacterShootingComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class UNREALSHOOTER_API UCharacterShootingComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	UPROPERTY()
	class AShooterCharacter *Character = nullptr;
	bool IsShooting = false;
	
protected:
	virtual void BeginPlay() override;

public:
	UCharacterShootingComponent();
	bool GetIsShooting() const { return IsShooting; }
	
	void StartShooting();
	void StopShooting();
	void Reload() const;
};
