// Copyright Atennop and Krypton. All Rights Reserved.

#include "Player/PlayerCharacterCrouchingComponent.h"
#include "Character/ShooterCharacter.h"
#include "Components/CapsuleComponent.h"

UPlayerCharacterCrouchingComponent::UPlayerCharacterCrouchingComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UPlayerCharacterCrouchingComponent::BeginPlay()
{
	Super::BeginPlay();
	Character = Cast<AShooterCharacter>(GetOwner());
	check(Character != nullptr)
	
	FOnTimelineFloat OnTimelineUpdate;
	OnTimelineUpdate.BindUFunction(this, "CrouchUpdate");
	CrouchingTimeline.AddInterpFloat(CrouchingCurve, OnTimelineUpdate);
	NormalHalfHeight = Character->GetCapsuleComponent()->GetUnscaledCapsuleHalfHeight();
}

void UPlayerCharacterCrouchingComponent::StartCrouching()
{
	if (Character->IsDead())
		return;
	
	IsCrouching = true;
	CrouchingTimeline.Play();
}

void UPlayerCharacterCrouchingComponent::StopCrouching()
{
	if (Character->IsDead())
		return;
	
	IsCrouching = false;
	CrouchingTimeline.Reverse();
}

void UPlayerCharacterCrouchingComponent::CrouchUpdate(float Alpha) const
{
	const float HalfHeight = FMath::Lerp(NormalHalfHeight, CrouchedHalfHeight, Alpha);
	Character->GetCapsuleComponent()->SetCapsuleHalfHeight(HalfHeight);
	Character->GetMesh()->SetRelativeLocation(FVector(0, 0, HalfHeight * -1));
}

void UPlayerCharacterCrouchingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	CrouchingTimeline.TickTimeline(DeltaTime);
}
