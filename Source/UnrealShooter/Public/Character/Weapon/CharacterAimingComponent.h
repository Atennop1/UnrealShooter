// Copyright Atennop and Krypton. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CharacterAimingComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class UNREALSHOOTER_API UCharacterAimingComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	UPROPERTY()
	class AShooterCharacter *Character = nullptr;

	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess))
	bool IsAiming = false;
	
protected:
	virtual void BeginPlay() override;

public:
	UCharacterAimingComponent();
	bool GetIsAiming() const { return IsAiming; }
	
	void StartAim();
	void StopAim();
};
