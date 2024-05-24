// Copyright Atennop and Krypton. All Rights Reserved.

#include "Character/ShooterCharacterRotatingComponent.h"
#include "Character/ShooterCharacter.h"

UShooterCharacterRotatingComponent::UShooterCharacterRotatingComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UShooterCharacterRotatingComponent::BeginPlay()
{
	Super::BeginPlay();
	Character = Cast<AShooterCharacter>(GetOwner());
	
	check(Character != nullptr)
	check(CharacterCamera != nullptr)
}

void UShooterCharacterRotatingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	LocationCameraPointingAt = CharacterCamera->GetComponentLocation() + CharacterCamera->GetForwardVector() * 500;
}

void UShooterCharacterRotatingComponent::Rotate(const FVector2D Input) const
{
	Character->AddControllerYawInput(Input.X);
	Character->AddControllerPitchInput(Input.Y);
	
	FVector CharacterForwardVector = Character->GetActorRotation().Vector();
	FVector CameraForwardVector = CharacterCamera->GetComponentRotation().Vector();
	CharacterForwardVector.Z = CameraForwardVector.Z = 0;

	if (const float Angle = FMath::RadiansToDegrees(FMath::Atan2(CameraForwardVector.Y * CharacterForwardVector.X - CameraForwardVector.X * CharacterForwardVector.Y, CameraForwardVector.X * CharacterForwardVector.X + CameraForwardVector.Y * CharacterForwardVector.Y)); FMath::Abs(Angle) > 45)
		Character->SetActorRotation(FRotator(0, Character->GetControlRotation().Yaw + 45 * (Angle > 0 ? -1 : 1), 0));
}
