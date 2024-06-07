// Copyright Atennop and Krypton. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/TimelineComponent.h"
#include "CharacterShootingComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class UNREALSHOOTER_API UCharacterShootingComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	UPROPERTY()
	class AShooterCharacter *Character = nullptr;

	UPROPERTY(BlueprintReadWrite, meta=(AllowPrivateAccess))
	class UCharacterWeaponRecoilingComponent *RecoilingComponent = nullptr;
	bool IsShooting = false;

	UPROPERTY(EditDefaultsOnly)
	UCurveFloat *SpreadCurve = nullptr;
	FTimeline SpreadingTimeline;
	float SpreadingCoefficient = 0;

	UFUNCTION()
	void OnSpreadUpdated(float Alpha);
	
protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	UCharacterShootingComponent();
	
	void StartShooting();
	void StopShooting();
};
