// Copyright Atennop and Krypton. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "Components/ActorComponent.h"
#include "CharacterRotatingComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class UNREALSHOOTER_API UCharacterRotatingComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	UPROPERTY()
	class AShooterCharacter *Character = nullptr;

	UPROPERTY(EditDefaultsOnly)
	float HalfDeadZoneAngle = 30;
	
	UPROPERTY(BlueprintReadWrite, meta=(AllowPrivateAccess))
	UCameraComponent *CharacterCamera = nullptr;

	UPROPERTY(BlueprintReadWrite, meta=(AllowPrivateAccess))
	FVector LocationCameraPointingAt;

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	UCharacterRotatingComponent();
	FVector GetLocationCameraPointingAt() const { return LocationCameraPointingAt; }
	void Rotate(const FVector2D Input) const;
};
