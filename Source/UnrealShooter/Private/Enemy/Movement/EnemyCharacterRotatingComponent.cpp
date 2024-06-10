// Copyright Atennop and Krypton. All Rights Reserved.

#include "Enemy/Movement/EnemyCharacterRotatingComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetStringLibrary.h"

UEnemyCharacterRotatingComponent::UEnemyCharacterRotatingComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UEnemyCharacterRotatingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	LocationCameraPointingAt = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)->GetMesh()->GetSocketLocation("head");
}

void UEnemyCharacterRotatingComponent::Rotate(const FVector2D Input) { }

FVector UEnemyCharacterRotatingComponent::GetLocationCameraPointingAt()
{
	return LocationCameraPointingAt;
}

FVector UEnemyCharacterRotatingComponent::GetInputOfThisFrame()
{
	return FVector::Zero();
}
