// Copyright Atennop. All Rights Reserved.

#include "Character/Weapon/CharacterWeaponRecoilingComponent.h"
#include "Character/ShooterCharacter.h"
#include "Curves/CurveVector.h"
#include "Weapon/IFirearm.h"

UCharacterWeaponRecoilingComponent::UCharacterWeaponRecoilingComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UCharacterWeaponRecoilingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	RecoilingTimeline.TickTimeline(DeltaTime);
	RevertingTimeline.TickTimeline(DeltaTime);

	const FVector InputRotation = Character->GetRotatingComponent()->GetInputOfThisFrame();
	InputRotationWhileRecoiling += FRotator(InputRotation.Y, InputRotation.X, 0);
}

void UCharacterWeaponRecoilingComponent::BeginPlay()
{
	Super::BeginPlay();
	Character = Cast<AShooterCharacter>(GetOwner());
	check(Character != nullptr)
}

void UCharacterWeaponRecoilingComponent::StartRecoil()
{
	if (IsRecoiling)
	{
		RecoilingTimeline.Play();
		return;
	}

	FOnTimelineVector RecoilingTrack;
	FOnTimelineFloat RevertingTrack;
	RecoilingTrack.BindUFunction(this, "OnRecoilingUpdated");
	RevertingTrack.BindUFunction(this, "OnReverting");

	RecoilingTimeline = RevertingTimeline = FTimeline();
	UCurveVector *RecoilingCurve = Cast<IFirearm>(&*Character->GetWeaponHoldingComponent()->GetHoldingWeapon())->GetData().RecoilingCurve;
	RecoilingTimeline.AddInterpVector(RecoilingCurve, RecoilingTrack);
	RevertingTimeline.AddInterpFloat(RevertingCurve, RevertingTrack);
	
	IsRecoiling = true;
	RecoilingTimeline.PlayFromStart();
	InputRotationWhileRecoiling = FRotator::ZeroRotator;
	OriginRecoilRotation = Character->GetControlRotation();
	GetWorld()->GetTimerManager().SetTimer(StopRecoilingTimerHandle, [&] { StopRecoil(); }, RecoilingCurve->FloatCurves[0].GetLastKey().Time, false);
}

void UCharacterWeaponRecoilingComponent::StopRecoil()
{
	if (!IsRecoiling)
		return;

	IsRecoiling = false;
	RecoilingTimeline.Stop();
	RevertingTimeline.PlayFromStart();
	GetWorld()->GetTimerManager().ClearTimer(StopRecoilingTimerHandle);
} 

void UCharacterWeaponRecoilingComponent::OnRecoilingUpdated(const FVector& Alpha)
{
	Character->AddControllerYawInput(Alpha.X);
	InputRotationWhileRecoiling.Yaw += Alpha.X * FMath::Sign(Character->GetRotatingComponent()->GetInputOfThisFrame().X) * (FMath::Sign(Character->GetRotatingComponent()->GetInputOfThisFrame().X) != FMath::Sign(Alpha.X) ? -1 : 1);
	
	Character->AddControllerPitchInput(Alpha.Y);
	InputRotationWhileRecoiling.Pitch += Alpha.Y * FMath::Sign(Character->GetRotatingComponent()->GetInputOfThisFrame().Y) * (FMath::Sign(Character->GetRotatingComponent()->GetInputOfThisFrame().Y) != FMath::Sign(Alpha.Y) ? -1 : 1);
}

void UCharacterWeaponRecoilingComponent::OnReverting(float Alpha) const
{
	const FRotator NewRotation = FMath::Lerp(Character->GetControlRotation(), OriginRecoilRotation + InputRotationWhileRecoiling, Alpha);
	Character->GetController()->SetControlRotation(NewRotation);
}
