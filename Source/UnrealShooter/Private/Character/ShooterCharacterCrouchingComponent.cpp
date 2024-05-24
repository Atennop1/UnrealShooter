// Copyright Atennop and Krypton. All Rights Reserved.

#include "Character/ShooterCharacterCrouchingComponent.h"
#include "Character/ShooterCharacter.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

UShooterCharacterCrouchingComponent::UShooterCharacterCrouchingComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UShooterCharacterCrouchingComponent::BeginPlay()
{
	Super::BeginPlay();
	Character = Cast<AShooterCharacter>(GetOwner());
	check(Character != nullptr)
		
	FOnTimelineFloat OnTimelineUpdate;
	NormalHalfHeight = Character->GetCapsuleComponent()->GetUnscaledCapsuleHalfHeight();
	NormalSpeed = Character->GetCharacterMovement()->MaxWalkSpeed;
	
	OnTimelineUpdate.BindUFunction(this, "CrouchUpdate");
	CrouchingTimeline.AddInterpFloat(CrouchingCurve, OnTimelineUpdate);
}

void UShooterCharacterCrouchingComponent::StartCrouching()
{
	IsCrouching = true;
	CrouchingTimeline.Play();
	Character->GetCharacterMovement()->MaxWalkSpeed = CrouchedSpeed;
}

void UShooterCharacterCrouchingComponent::StopCrouching()
{
	IsCrouching = false;
	CrouchingTimeline.Reverse();
	Character->GetCharacterMovement()->MaxWalkSpeed = NormalSpeed;
}

// ReSharper disable once CppMemberFunctionMayBeConst
void UShooterCharacterCrouchingComponent::CrouchUpdate(const float Alpha)
{
	const float HalfHeight = FMath::Lerp(NormalHalfHeight, CrouchedHalfHeight, Alpha);
	Character->GetCapsuleComponent()->SetCapsuleHalfHeight(HalfHeight);
	Character->GetMesh()->SetRelativeLocation(FVector(0, 0, HalfHeight * -1));
}

void UShooterCharacterCrouchingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	CrouchingTimeline.TickTimeline(DeltaTime);
}
