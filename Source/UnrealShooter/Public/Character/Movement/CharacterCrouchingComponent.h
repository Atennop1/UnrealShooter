// Copyright Atennop and Krypton. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/TimelineComponent.h"
#include "CharacterCrouchingComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class UNREALSHOOTER_API UCharacterCrouchingComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	UPROPERTY()
	class AShooterCharacter *Character = nullptr;
	
	UPROPERTY(EditDefaultsOnly)
	UCurveFloat *CrouchingCurve = nullptr;
	FTimeline CrouchingTimeline;
	bool IsCrouching = false;

	UPROPERTY(EditDefaultsOnly)
	float CrouchedHalfHeight = 50;
	float NormalHalfHeight = 100;

	UFUNCTION()
	void CrouchUpdate(float Alpha) const;

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	UCharacterCrouchingComponent();

	void StartCrouching();
	void StopCrouching();

	UFUNCTION(BlueprintCallable)
	bool GetIsCrouching() const { return IsCrouching; }
};
