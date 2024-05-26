// Copyright Atennop and Krypton. All Rights Reserved.

#include "Character/Movement/CharacterCrouchingComponent.h"
#include "Character/ShooterCharacter.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

UCharacterCrouchingComponent::UCharacterCrouchingComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UCharacterCrouchingComponent::BeginPlay()
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

void UCharacterCrouchingComponent::StartCrouching()
{
	IsCrouching = true;
	CrouchingTimeline.Play();
	Character->GetCharacterMovement()->MaxWalkSpeed = CrouchedSpeed;
}

void UCharacterCrouchingComponent::StopCrouching()
{
	IsCrouching = false;
	CrouchingTimeline.Reverse();
	Character->GetCharacterMovement()->MaxWalkSpeed = NormalSpeed;
}

// ReSharper disable once CppMemberFunctionMayBeConst
void UCharacterCrouchingComponent::CrouchUpdate(const float Alpha)
{
	const float HalfHeight = FMath::Lerp(NormalHalfHeight, CrouchedHalfHeight, Alpha);
	Character->GetCapsuleComponent()->SetCapsuleHalfHeight(HalfHeight);
	Character->GetMesh()->SetRelativeLocation(FVector(0, 0, HalfHeight * -1));
}

void UCharacterCrouchingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	CrouchingTimeline.TickTimeline(DeltaTime);
}
