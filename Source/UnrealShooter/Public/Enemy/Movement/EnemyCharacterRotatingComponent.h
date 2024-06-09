// Copyright Atennop and Krypton. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Character/Movement/ICharacterRotatingComponent.h"
#include "Components/ActorComponent.h"
#include "EnemyCharacterRotatingComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class UNREALSHOOTER_API UEnemyCharacterRotatingComponent : public UActorComponent, public ICharacterRotatingComponent
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly)
	FVector LocationCameraPointingAt;

public:
	UEnemyCharacterRotatingComponent();
	virtual void Rotate(const FVector2D Input) override;
	
	virtual FVector GetLocationCameraPointingAt() override;
	virtual FVector GetInputOfThisFrame() override;
};
