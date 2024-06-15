// Copyright Atennop and Krypton. All Rights Reserved.

#include "Enemy/Components/EnemyCharacterRotatingComponent.h"
#include "AIController.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

void UEnemyCharacterRotatingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	const bool IsLookingAtPlayer = Cast<AAIController>(Cast<ACharacter>(GetOwner())->GetController())->GetFocusActor() != nullptr;
	LocationCameraPointingAt = IsLookingAtPlayer ? UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)->GetMesh()->GetSocketLocation("head") : GetOwner()->GetActorLocation() + GetOwner()->GetActorForwardVector() * 50 + FVector(0, 0, 50);
}