// Copyright Atennop and Krypton. All Rights Reserved.

#include "Character/Weapon/CharacterPickingComponent.h"
#include "Character/ShooterCharacter.h"
#include "Weapon/IFirearm.h"
#include "Weapon/Pickables/IAmmoPickable.h"
#include "Weapon/Pickables/IFirearmPickable.h"
#include "Weapon/Pickables/IWeaponPickable.h"

UCharacterPickingComponent::UCharacterPickingComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UCharacterPickingComponent::BeginPlay()
{
	Super::BeginPlay();
	Character = Cast<AShooterCharacter>(GetOwner());
	check(Character != nullptr);
}

void UCharacterPickingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (Character->IsDead())
		return;

	TArray<AActor*> Actors;
	Character->GetOverlappingActors(Actors);

	for (const auto Actor : Actors)
	{
		if (IAmmoPickable *AmmoPickable = Cast<IAmmoPickable>(Actor); AmmoPickable != nullptr && Character->GetWeaponHoldingComponent()->GetIsHolding() && AmmoPickable->GetAmmoType() == Character->GetWeaponHoldingComponent()->GetHoldingWeapon()->GetWeaponType())
		{
			IFirearm *Firearm = Cast<IFirearm>(&*Character->GetWeaponHoldingComponent()->GetHoldingWeapon());
			Firearm->SetState(FFirearmState(Firearm->GetState().AmmoInMagazine, Firearm->GetState().AmmoInStock + AmmoPickable->GetAmountOfAmmo()));
			GetWorld()->DestroyActor(Actor);
		}
		
		if (Actor->Implements<UWeaponPickable>() && PickablesToWeapons.Contains(Actor->GetClass()) && !Character->GetWeaponHoldingComponent()->GetIsHolding())
		{
			const auto WeaponActor = GetWorld()->SpawnActor(PickablesToWeapons[Actor->GetClass()]);
			TScriptInterface<IWeapon> Weapon;
			Weapon.SetInterface(Cast<IWeapon>(WeaponActor));
			Weapon.SetObject(WeaponActor);

			if (const auto FirearmPickable = Cast<IFirearmPickable>(Actor); FirearmPickable != nullptr)
				Cast<IFirearm>(WeaponActor)->SetState(FirearmPickable->GetState());

			Character->GetWeaponHoldingComponent()->Hold(Weapon);
			GetWorld()->DestroyActor(Actor);
		}
	}
}
