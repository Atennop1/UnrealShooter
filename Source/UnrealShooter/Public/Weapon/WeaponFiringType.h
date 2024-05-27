// Copyright Atennop and Krypton. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "WeaponFiringType.generated.h"

UENUM(BlueprintType)
enum class EWeaponFiringType : uint8
{
	Tapping UMETA(DisplayName = "Tapping"),
	Spraying UMETA(DisplayName = "Spraying")
};
