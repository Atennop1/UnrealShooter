// Copyright Atennop and Krypton. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ICharacterCrouchingComponent.generated.h"

UINTERFACE(MinimalAPI, NotBlueprintable)
class UCharacterCrouchingComponent : public UInterface
{
	GENERATED_BODY()
};

class UNREALSHOOTER_API ICharacterCrouchingComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	virtual bool GetIsCrouching() = 0;
	
	virtual void StartCrouching() = 0;
	virtual void StopCrouching() = 0;
};
