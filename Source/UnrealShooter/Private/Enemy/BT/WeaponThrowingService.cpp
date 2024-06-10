// Copyright Atennop and Krypton. All Rights Reserved.

#include "Enemy/BT/WeaponThrowingService.h"
#include "AIController.h"
#include "Character/ShooterCharacter.h"
#include "Weapon/Interfaces/IFirearm.h"

UWeaponThrowingService::UWeaponThrowingService()
{
	NodeName = TEXT("Weapon Throwing Service");
}

void UWeaponThrowingService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	const AShooterCharacter *Enemy = Cast<AShooterCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	
	if (Enemy->GetWeaponHoldingComponent()->GetIsHolding() && Enemy->GetWeaponHoldingComponent()->GetHoldingWeapon().GetObject()->GetClass()->ImplementsInterface(UFirearm::StaticClass()))
	{
		const FFirearmState FirearmState = Cast<IFirearm>(&*Enemy->GetWeaponHoldingComponent()->GetHoldingWeapon())->GetState();
		
		if (FirearmState.AmmoInMagazine == 0 && FirearmState.AmmoInStock == 0)
			Enemy->GetWeaponThrowingComponent()->Throw();
	}
}
