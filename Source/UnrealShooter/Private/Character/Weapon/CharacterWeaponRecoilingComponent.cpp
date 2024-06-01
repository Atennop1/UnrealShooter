// Copyright Atennop and Krypton. All Rights Reserved.

#include "Character/Weapon/CharacterWeaponRecoilingComponent.h"
#include "Character/ShooterCharacter.h"
#include "Kismet/KismetMathLibrary.h"

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
	FOnTimelineEvent FinishedEvent;
	RecoilingTrack.BindUFunction(this, "OnRecoilingUpdated");
	RevertingTrack.BindUFunction(this, "OnReverting");
	FinishedEvent.BindUFunction(this, "StopRecoil");

	RecoilingTimeline = FTimeline();
	RecoilingTimeline.AddInterpVector(Cast<IFirearm>(&*Character->GetWeaponHoldingComponent()->GetHoldingWeapon())->GetData().RecoilingCurve, RecoilingTrack);
	RevertingTimeline.AddInterpFloat(RevertingCurve, RevertingTrack);
	RevertingTimeline.SetTimelineFinishedFunc(FinishedEvent);
	
	IsRecoiling = true;
	RecoilingTimeline.PlayFromStart();
	InputRotationWhileRecoiling = FRotator(0, 0, 0);
	OriginRecoilRotation = Character->GetControlRotation();
}

void UCharacterWeaponRecoilingComponent::StopRecoil()
{
	GEngine->AddOnScreenDebugMessage(-1, 9, FColor::Cyan, "AAA");
	
	if (!IsRecoiling)
		return;
	
	IsRecoiling = false;
	RecoilingTimeline.Stop();
	RevertingTimeline.PlayFromStart();
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
	const FRotator NewRotation = UKismetMathLibrary::RLerp(Character->GetControlRotation(), OriginRecoilRotation + InputRotationWhileRecoiling, Alpha, true);
	Character->GetController()->SetControlRotation(NewRotation);
}
