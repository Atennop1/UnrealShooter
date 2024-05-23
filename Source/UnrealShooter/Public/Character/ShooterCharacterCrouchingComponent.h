// Copyright Atennop and Krypton. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/TimelineComponent.h"
#include "ShooterCharacterCrouchingComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class UNREALSHOOTER_API UShooterCharacterCrouchingComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	UPROPERTY()
	class AShooterCharacter *Character = nullptr;
	
	UPROPERTY(EditDefaultsOnly)
	UCurveFloat *CrouchingCurve = nullptr;
	FTimeline CrouchingTimeline;

	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess))
	bool IsCrouching = false;

	UPROPERTY(EditDefaultsOnly)
	float CrouchedHalfHeight = 50;
	float NormalHalfHeight = 100;

	UPROPERTY(EditDefaultsOnly)
	float CrouchedSpeed = 300;
	float NormalSpeed = 600;

	UFUNCTION()
	void CrouchUpdate(float Alpha);

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	UShooterCharacterCrouchingComponent();
	void StartCrouching();
	void StopCrouching();
};
