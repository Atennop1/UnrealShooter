// Copyright Atennop and Krypton. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "Character/Movement/ICharacterRotatingComponent.h"
#include "Components/ActorComponent.h"
#include "PlayerCharacterRotatingComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class UNREALSHOOTER_API UPlayerCharacterRotatingComponent : public UActorComponent, public ICharacterRotatingComponent
{
	GENERATED_BODY()

private:
	UPROPERTY()
	class AShooterCharacter *Character = nullptr;

	UPROPERTY(EditDefaultsOnly)
	float HalfDeadZoneAngle = 30;
	
	UPROPERTY(BlueprintReadWrite, meta=(AllowPrivateAccess))
	UCameraComponent *CharacterCamera = nullptr;

	FVector LocationCameraPointingAt;
	FVector InputOfThisFrame;

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	UPlayerCharacterRotatingComponent();

	virtual void Rotate(const FVector2D Input) override;
	virtual FVector GetLocationCameraPointingAt() override { return LocationCameraPointingAt; }
	virtual FVector GetInputOfThisFrame() override { return InputOfThisFrame; }
};
