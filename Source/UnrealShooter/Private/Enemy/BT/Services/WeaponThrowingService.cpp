// Copyright Atennop and Krypton. All Rights Reserved.

#include "Enemy/BT/Services/WeaponThrowingService.h"
#include "AIController.h"
#include "Enemy/EnemyCharacter.h"
#include "Weapon/IFirearm.h"

UWeaponThrowingService::UWeaponThrowingService()
{
	NodeName = TEXT("Weapon Throwing Service");
}

void UWeaponThrowingService::ReceiveTick(UBehaviorTreeComponent& OwnerComp)
{
	const AEnemyCharacter *Enemy = Cast<AEnemyCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	
	if (Enemy->GetWeaponHoldingComponent()->GetIsHolding() && Enemy->GetWeaponHoldingComponent()->GetHoldingWeapon().GetObject()->GetClass()->ImplementsInterface(UFirearm::StaticClass()))
	{
		const FFirearmState FirearmState = Cast<IFirearm>(&*Enemy->GetWeaponHoldingComponent()->GetHoldingWeapon())->GetState();
		
		if (FirearmState.AmmoInMagazine == 0 && FirearmState.AmmoInStock == 0)
			Enemy->GetWeaponThrowingComponent()->Throw();
	}
}
