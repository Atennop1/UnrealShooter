// Copyright Atennop and Krypton. All Rights Reserved.

#include "Character/CharacterRotatingComponent.h"
#include "Character/ShooterCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

UCharacterRotatingComponent::UCharacterRotatingComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UCharacterRotatingComponent::BeginPlay()
{
	Super::BeginPlay();
	Character = Cast<AShooterCharacter>(GetOwner());
	
	check(Character != nullptr)
	check(CharacterCamera != nullptr)
}

void UCharacterRotatingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	LocationCameraPointingAt = CharacterCamera->GetComponentLocation() + CharacterCamera->GetForwardVector() * 500;
	Character->GetCharacterMovement()->bUseControllerDesiredRotation = Character->GetVelocity() != FVector::Zero();
}

void UCharacterRotatingComponent::Rotate(const FVector2D Input) const
{
	Character->AddControllerYawInput(Input.X);
	Character->AddControllerPitchInput(Input.Y);

	FVector CharacterForwardVector = Character->GetActorRotation().Vector();
	FVector CameraForwardVector = CharacterCamera->GetComponentRotation().Vector();
	CharacterForwardVector.Z = CameraForwardVector.Z = 0;

	if (const float Angle = FMath::RadiansToDegrees(FMath::Atan2(CameraForwardVector.Y * CharacterForwardVector.X - CameraForwardVector.X * CharacterForwardVector.Y, CameraForwardVector.X * CharacterForwardVector.X + CameraForwardVector.Y * CharacterForwardVector.Y)); FMath::Abs(Angle) > HalfDeadZoneAngle)
		Character->SetActorRotation(FRotator(0, Character->GetControlRotation().Yaw + HalfDeadZoneAngle * (Angle > 0 ? -1 : 1), 0));
}
