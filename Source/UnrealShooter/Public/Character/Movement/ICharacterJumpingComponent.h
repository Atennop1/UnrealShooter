// Copyright Atennop and Krypton. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ICharacterJumpingComponent.generated.h"

UINTERFACE(MinimalAPI, NotBlueprintable)
class UCharacterJumpingComponent : public UInterface
{
	GENERATED_BODY()
};

class UNREALSHOOTER_API ICharacterJumpingComponent
{
	GENERATED_BODY()

public:
	virtual void StartJumping() = 0;
	virtual void StopJumping() = 0;
};
