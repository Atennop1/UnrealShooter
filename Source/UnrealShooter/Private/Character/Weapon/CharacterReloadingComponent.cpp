// Copyright Atennop and Krypton. All Rights Reserved.

#include "Character/Weapon/CharacterReloadingComponent.h"
#include "Character/ShooterCharacter.h"
#include "Weapon/Interfaces/IFirearm.h"

UCharacterReloadingComponent::UCharacterReloadingComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UCharacterReloadingComponent::BeginPlay()
{
	Super::BeginPlay();
	Character = Cast<AShooterCharacter>(GetOwner());
	check(Character != nullptr);
}

void UCharacterReloadingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (Character->GetWeaponHoldingComponent()->GetIsHolding())
		return;
	
	if (OldMagazine)
		GetWorld()->DestroyActor(OldMagazine);
		
	if (NewMagazine)
		GetWorld()->DestroyActor(NewMagazine);
}

void UCharacterReloadingComponent::Reload()
{
	if (!Character->GetWeaponHoldingComponent()->GetIsHolding() || !Character->GetWeaponHoldingComponent()->GetHoldingWeapon().GetObject()->GetClass()->ImplementsInterface(UFirearm::StaticClass()))
		return;

	if (IFirearm* Weapon = Cast<IFirearm>(&*Character->GetWeaponHoldingComponent()->GetHoldingWeapon()); !Weapon->GetIsReloading())
	{
		const AActor *WeaponActor = Cast<AActor>(Character->GetWeaponHoldingComponent()->GetHoldingWeapon().GetObject());
		WeaponMesh = Cast<USkeletalMeshComponent>(WeaponActor->GetComponentByClass(USkeletalMeshComponent::StaticClass()));
		
		OldMagazine = NewMagazine = nullptr;
		Weapon->Reload();
	}
}

bool UCharacterReloadingComponent::IsReloading() const
{
	return Character != nullptr && Character->GetWeaponHoldingComponent() != nullptr && Character->GetWeaponHoldingComponent()->GetIsHolding() &&
		Character->GetWeaponHoldingComponent()->GetHoldingWeapon().GetObject()->GetClass()->ImplementsInterface(UFirearm::StaticClass()) &&
		Cast<IFirearm>(&*Character->GetWeaponHoldingComponent()->GetHoldingWeapon())->GetIsReloading();
}

void UCharacterReloadingComponent::RemoveMagazine()
{
	const UClass *WeaponClass = Character->GetWeaponHoldingComponent()->GetHoldingWeapon().GetObject()->GetClass();
	OldMagazine = GetWorld()->SpawnActor(WeaponsToMagazines[WeaponClass]);
	OldMagazine->AttachToComponent(Character->GetCharacterMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), WeaponsToMagazineSockets[WeaponClass]);
	WeaponMesh->HideBoneByName(WeaponsToHidingBones[WeaponClass], PBO_None);
}

void UCharacterReloadingComponent::DropMagazine() const
{
	FTimerHandle MagazineDestroyingHandle;
	GetWorld()->GetTimerManager().SetTimer(MagazineDestroyingHandle, [&] { if (OldMagazine) GetWorld()->DestroyActor(OldMagazine); }, 5, false);
	Cast<UStaticMeshComponent>(OldMagazine->GetComponentByClass(UStaticMeshComponent::StaticClass()))->SetSimulatePhysics(true);
}

void UCharacterReloadingComponent::TakeMagazine()
{
	const UClass *WeaponClass = Character->GetWeaponHoldingComponent()->GetHoldingWeapon().GetObject()->GetClass();
	NewMagazine = GetWorld()->SpawnActor(WeaponsToMagazines[WeaponClass]);
	NewMagazine->AttachToComponent(Character->GetCharacterMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), WeaponsToMagazineSockets[WeaponClass]);
}

void UCharacterReloadingComponent::PlaceMagazine()
{
	if (NewMagazine)
		GetWorld()->DestroyActor(NewMagazine);
	
	WeaponMesh->UnHideBoneByName(WeaponsToHidingBones[Character->GetWeaponHoldingComponent()->GetHoldingWeapon().GetObject()->GetClass()]);
}

