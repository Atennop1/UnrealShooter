// Copyright Atennop and Krypton. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ICharacterRotatingComponent.generated.h"

UINTERFACE(MinimalAPI, NotBlueprintable)
class UCharacterRotatingComponent : public UInterface
{
	GENERATED_BODY()
};

class UNREALSHOOTER_API ICharacterRotatingComponent
{
	GENERATED_BODY()

public: 
	virtual void Rotate(const FVector2D Input) = 0;
	virtual FVector GetInputOfThisFrame() = 0;

	UFUNCTION(BlueprintCallable)
	virtual FVector GetLocationCameraPointingAt() = 0;
};
