// Copyright Atennop and Krypton. All Rights Reserved.

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
	
	UPROPERTY(EditDefaultsOnly)
	UCurveFloat *RecoilYawCurve = nullptr;

	UPROPERTY(EditDefaultsOnly)
	UCurveFloat *RecoilPitchCurve = nullptr;

	bool IsRecoiling = false;
	FTimeline RecoilingTimeline;
	FTimeline RevertingTimeline;

	FRotator RecoiledRotation;
	FRotator OriginRecoilRotation;
	FRotator PostRecoilRotation;

	UFUNCTION()
	void OnYawUpdated(float Alpha);

	UFUNCTION()
	void OnPitchUpdated(float Alpha);

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
