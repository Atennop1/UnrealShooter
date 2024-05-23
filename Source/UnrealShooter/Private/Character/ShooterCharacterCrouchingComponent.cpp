﻿// Copyright Atennop and Krypton. All Rights Reserved.

#include "Character/ShooterCharacterCrouchingComponent.h"
#include "Character/ShooterCharacter.h"
#include "Components/CapsuleComponent.h"

UShooterCharacterCrouchingComponent::UShooterCharacterCrouchingComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UShooterCharacterCrouchingComponent::BeginPlay()
{
	Super::BeginPlay();
	Character = Cast<AShooterCharacter>(GetOwner());

	if (Character == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 999, FColor::Red, "ShooterCharacterCrouchingComponent must be on ShooterCharacter!");
		return;
	}
		
	FOnTimelineFloat OnTimelineUpdate;
	NormalHalfHeight = Character->GetCapsuleComponent()->GetUnscaledCapsuleHalfHeight();
	
	OnTimelineUpdate.BindUFunction(this, "CrouchUpdate");
	CrouchingTimeline.AddInterpFloat(CrouchingCurve, OnTimelineUpdate);
}

// ReSharper disable once CppMemberFunctionMayBeConst
void UShooterCharacterCrouchingComponent::CrouchUpdate(const float Alpha)
{
	const float HalfHeight = FMath::Lerp(NormalHalfHeight, CrouchedHalfHeight, Alpha);
	Character->GetCapsuleComponent()->SetCapsuleHalfHeight(HalfHeight);
}

void UShooterCharacterCrouchingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	CrouchingTimeline.TickTimeline(DeltaTime);
}

void UShooterCharacterCrouchingComponent::StartCrouching()
{
	IsCrouched = true;
	CrouchingTimeline.Play();
}

void UShooterCharacterCrouchingComponent::StopCrouching()
{
	IsCrouched = false;
	CrouchingTimeline.Reverse();
}
