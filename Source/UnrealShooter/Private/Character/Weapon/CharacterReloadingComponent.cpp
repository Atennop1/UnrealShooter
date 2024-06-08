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
	if (Character->IsDead() || !Character->GetWeaponHoldingComponent()->GetIsHolding() || !Character->GetWeaponHoldingComponent()->GetHoldingWeapon().GetObject()->GetClass()->ImplementsInterface(UFirearm::StaticClass()))
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
	OldMagazine->AttachToComponent(Character->GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), WeaponsToMagazineSockets[WeaponClass]);
	WeaponMesh->HideBoneByName(WeaponsToHidingBones[WeaponClass], PBO_None);
}

void UCharacterReloadingComponent::DropMagazine() const
{
	OldMagazine->SetLifeSpan(5);
	UStaticMeshComponent *OldMagazineMesh = Cast<UStaticMeshComponent>(OldMagazine->GetComponentByClass(UStaticMeshComponent::StaticClass()));
	
	OldMagazineMesh->SetSimulatePhysics(true);
	OldMagazineMesh->AddForce(MagazineDroppingForce * -Character->GetActorRightVector() / OldMagazineMesh->GetMass());
}

void UCharacterReloadingComponent::TakeMagazine()
{
	const UClass *WeaponClass = Character->GetWeaponHoldingComponent()->GetHoldingWeapon().GetObject()->GetClass();
	NewMagazine = GetWorld()->SpawnActor(WeaponsToMagazines[WeaponClass]);
	NewMagazine->AttachToComponent(Character->GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), WeaponsToMagazineSockets[WeaponClass]);
}

void UCharacterReloadingComponent::PlaceMagazine()
{
	if (NewMagazine)
		GetWorld()->DestroyActor(NewMagazine);
	
	WeaponMesh->UnHideBoneByName(WeaponsToHidingBones[Character->GetWeaponHoldingComponent()->GetHoldingWeapon().GetObject()->GetClass()]);
}

