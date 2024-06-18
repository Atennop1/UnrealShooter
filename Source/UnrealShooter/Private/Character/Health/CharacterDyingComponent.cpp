// Copyright Atennop. All Rights Reserved.

#include "Character/Health/CharacterDyingComponent.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Character/ShooterCharacter.h"
#include "Components/CapsuleComponent.h"

UCharacterDyingComponent::UCharacterDyingComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UCharacterDyingComponent::BeginPlay()
{
	Super::BeginPlay();
	Character = Cast<AShooterCharacter>(GetOwner());
	check(Character != nullptr);
}

void UCharacterDyingComponent::Die()
{
	if (UCameraComponent *Camera = Cast<UCameraComponent>(GetOwner()->GetComponentByClass(UCameraComponent::StaticClass())); IsValid(Camera))
	{
		Camera->AttachToComponent(ComponentToAttachCamera, FAttachmentTransformRules(EAttachmentRule::KeepWorld, false));
		Camera->SetRelativeTransform(CameraTransformAfterDeath);
	}

	Character->GetWeaponThrowingComponent()->Throw();
	Character->GetMesh()->SetAllBodiesSimulatePhysics(true);
	Character->GetCapsuleComponent()->DestroyComponent();
	Character->GetController()->SetControlRotation(CameraTransformAfterDeath.Rotator());
	
	GetWorld()->GetTimerManager().SetTimer(DyingTimerHandle, [&]
	{
		if (IsValid(Character))
			Character->Destroy();
		
		if (IsValid(DeathScreen))
		{
			UWidgetLayoutLibrary::RemoveAllWidgets(GetWorld());
			DeathScreen->AddToViewport(0);
		}
	}, DyingTime, false);
}

void UCharacterDyingComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	GetWorld()->GetTimerManager().ClearTimer(DyingTimerHandle);
}
