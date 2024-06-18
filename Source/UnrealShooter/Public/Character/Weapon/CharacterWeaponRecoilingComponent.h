// Copyright Atennop. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/TimelineComponent.h"
#include "CharacterWeaponRecoilingComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class UNREALSHOOTER_API UCharacterWeaponRecoilingComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	UPROPERTY()
	class AShooterCharacter *Character = nullptr;

	UPROPERTY(EditDefaultsOnly)
	UCurveFloat *RevertingCurve = nullptr;

	bool IsRecoiling = false;
	FTimeline RecoilingTimeline;
	FTimeline RevertingTimeline;
	FTimerHandle StopRecoilingTimerHandle;

	FRotator InputRotationWhileRecoiling;
	FRotator OriginRecoilRotation;

	UFUNCTION()
	void OnRecoilingUpdated(const FVector& Alpha);

	UFUNCTION()
	void OnReverting(float Alpha) const;
	
protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	UCharacterWeaponRecoilingComponent();
	
	void StartRecoil();
	void StopRecoil();
};
