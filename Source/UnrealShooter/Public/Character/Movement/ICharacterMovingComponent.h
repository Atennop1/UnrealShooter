// Copyright Atennop and Krypton. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ICharacterMovingComponent.generated.h"

UINTERFACE(MinimalAPI, NotBlueprintable)
class UCharacterMovingComponent : public UInterface
{
	GENERATED_BODY()
};

class UNREALSHOOTER_API ICharacterMovingComponent
{
	GENERATED_BODY()

public:
	virtual void Move(const FVector2D Input) = 0;
};
