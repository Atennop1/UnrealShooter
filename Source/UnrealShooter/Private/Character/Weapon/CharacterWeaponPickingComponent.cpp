// Copyright Atennop and Krypton. All Rights Reserved.

#include "Character/Weapon/CharacterWeaponPickingComponent.h"

#include "Character/ShooterCharacter.h"
#include "Character/Weapon/CharacterWeaponHoldingComponent.h"
#include "Weapon/Interfaces/IFirearm.h"
#include "Weapon/Interfaces/IWeaponPickable.h"

UCharacterWeaponPickingComponent::UCharacterWeaponPickingComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UCharacterWeaponPickingComponent::BeginPlay()
{
	Super::BeginPlay();
	Character = Cast<AShooterCharacter>(GetOwner());
	check(Character != nullptr);
}

void UCharacterWeaponPickingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (Character->GetWeaponHoldingComponent()->GetIsHolding())
		return;

	TArray<AActor*> Actors;
	Character->GetOverlappingActors(Actors);

	for (const auto Actor : Actors)
	{
		if (!Actor->Implements<UWeaponPickable>() || !PickablesToWeapons.Contains(Actor->GetClass()))
			return;
			
		const auto WeaponActor = GetWorld()->SpawnActor(PickablesToWeapons[Actor->GetClass()]);
		TScriptInterface<IWeapon> Weapon;
		Weapon.SetInterface(Cast<IWeapon>(WeaponActor));
		Weapon.SetObject(WeaponActor);
		
		Character->GetWeaponHoldingComponent()->Hold(Weapon);
		GetWorld()->DestroyActor(Actor);
	}
}

