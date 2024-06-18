// Copyright Atennop. All Rights Reserved.

#include "Character/Health/HealthPickable.h"

AHealthPickable::AHealthPickable() : HealthToAdd(0)
{
	PrimaryActorTick.bCanEverTick = false;
}
