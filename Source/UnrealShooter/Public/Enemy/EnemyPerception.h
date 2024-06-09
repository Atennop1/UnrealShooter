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
	UPROPERTY()
	AEnemyController *Controller = nullptr;
	FTimerHandle ChasingTimerHandle;

	UPROPERTY(EditDefaultsOnly)
	FName TargetVariableName = "";

	UPROPERTY(EditDefaultsOnly)
	float LoosingTargetTime = 3.0f;

	UFUNCTION()
	void OnPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);
	
protected:
	virtual void BeginPlay() override;

public:
	UEnemyPerception();
};
