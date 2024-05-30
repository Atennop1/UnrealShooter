// Copyright Atennop and Krypton. All Rights Reserved.

#include "Character/Weapon/CharacterWeaponRecoilingComponent.h"
#include "Character/ShooterCharacter.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetStringLibrary.h"

UCharacterWeaponRecoilingComponent::UCharacterWeaponRecoilingComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UCharacterWeaponRecoilingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	RecoilingTimeline.TickTimeline(DeltaTime);
	RevertingTimeline.TickTimeline(DeltaTime);
}

void UCharacterWeaponRecoilingComponent::BeginPlay()
{
	Super::BeginPlay();
	Character = Cast<AShooterCharacter>(GetOwner());
	check(Character != nullptr)
	
	FOnTimelineFloat YawTrack;
	FOnTimelineFloat PitchTrack;
	FOnTimelineFloat RevertingTrack;
	YawTrack.BindUFunction(this, "OnYawUpdated");
	PitchTrack.BindUFunction(this, "OnPitchUpdated");
	RevertingTrack.BindUFunction(this, "OnReverting");
	
	RecoilingTimeline.AddInterpFloat(RecoilYawCurve, YawTrack);
	RecoilingTimeline.AddInterpFloat(RecoilPitchCurve, PitchTrack);
	RevertingTimeline.AddInterpFloat(RevertingCurve, RevertingTrack);
}

void UCharacterWeaponRecoilingComponent::StartRecoil()
{
	if (IsRecoiling)
	{
		RecoilingTimeline.Play();
		return;
	}
	
	IsRecoiling = true;
	RecoilingTimeline.PlayFromStart();
	RecoiledRotation = FRotator(0, 0, 0);
	OriginRecoilRotation = Character->GetControlRotation();
}

void UCharacterWeaponRecoilingComponent::StopRecoil()
{
	if (!IsRecoiling)
		return;
	
	IsRecoiling = false;
	RecoilingTimeline.Stop();
	RevertingTimeline.PlayFromStart();
	PostRecoilRotation = Character->GetControlRotation();
}

void UCharacterWeaponRecoilingComponent::OnYawUpdated(float Alpha)
{
	Character->AddControllerYawInput(Alpha);
	RecoiledRotation.Yaw += Alpha;
}

void UCharacterWeaponRecoilingComponent::OnPitchUpdated(float Alpha)
{
	Character->AddControllerPitchInput(Alpha);
	RecoiledRotation.Pitch += Alpha;
}

void UCharacterWeaponRecoilingComponent::OnReverting(float Alpha) const
{
	const FRotator RotationToAdd = FRotator(UKismetMathLibrary::Lerp(PostRecoilRotation.Pitch, (PostRecoilRotation - RecoiledRotation).Pitch, Alpha),
		UKismetMathLibrary::Lerp(PostRecoilRotation.Yaw, (PostRecoilRotation - RecoiledRotation).Yaw, Alpha),
		UKismetMathLibrary::Lerp(PostRecoilRotation.Roll, (PostRecoilRotation - RecoiledRotation).Roll, Alpha)) - PostRecoilRotation;
	GEngine->AddOnScreenDebugMessage(-1, 9, FColor::Cyan, UKismetStringLibrary::Conv_RotatorToString(RotationToAdd));

	Character->AddControllerYawInput(RotationToAdd.Yaw / 8);
	Character->AddControllerPitchInput(RotationToAdd.Pitch / 8);
}

