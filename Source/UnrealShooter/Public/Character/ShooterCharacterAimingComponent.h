// Copyright Atennop and Krypton. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ShooterCharacterAimingComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class UNREALSHOOTER_API UShooterCharacterAimingComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	UPROPERTY()
	class AShooterCharacter *Character = nullptr;

	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess))
	bool IsAiming = true;
	
protected:
	virtual void BeginPlay() override;

public:
	UShooterCharacterAimingComponent();
	bool GetIsAiming() const { return IsAiming; }
	
	void StartAim();
	void StopAim();
};
