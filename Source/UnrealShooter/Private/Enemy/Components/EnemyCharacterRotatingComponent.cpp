// Copyright Atennop and Krypton. All Rights Reserved.

#include "Enemy/Components/EnemyCharacterRotatingComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

void UEnemyCharacterRotatingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	LocationCameraPointingAt = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)->GetMesh()->GetSocketLocation("head");
}