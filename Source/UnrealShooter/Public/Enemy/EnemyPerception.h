// Copyright Atennop and Krypton. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "EnemyController.h"
#include "Perception/AIPerceptionComponent.h"
#include "EnemyPerception.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class UNREALSHOOTER_API UEnemyPerception : public UAIPerceptionComponent
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly)
	float LoosingTargetTime = 3.0f;

	UPROPERTY(EditDefaultsOnly)
	FName IsHearingPlayerVariableName = "IsHearingPlayer";
	
	UPROPERTY(EditDefaultsOnly)
	FName CanSeePlayerVariableName = "CanSeePlayer";
	
	UPROPERTY(EditDefaultsOnly)
	FName TargetVariableName = "TargetActor";

	UPROPERTY(EditDefaultsOnly)
	FName TargetLocationVariableName = "TargetLocation";

	UPROPERTY()
	AActor *SensedActor = nullptr;
	
	UPROPERTY()
	AEnemyController *Controller = nullptr;
	FTimerHandle ChasingTimerHandle;

	UFUNCTION()
	void OnPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);
	
protected:
	virtual void BeginPlay() override;

public:
	UEnemyPerception();
};
