// Copyright Atennop. All Rights Reserved.

#include "Enemy/BT/Services/ReloadingService.h"
#include "AIController.h"
#include "Enemy/EnemyCharacter.h"
#include "Weapon/IFirearm.h"

UReloadingService::UReloadingService()
{
	NodeName = TEXT("Reloading Service");
}

void UReloadingService::ReceiveTick(UBehaviorTreeComponent& OwnerComp)
{
	const AEnemyCharacter *Enemy = Cast<AEnemyCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	
	if (Enemy->GetWeaponHoldingComponent()->GetIsHolding() && Enemy->GetWeaponHoldingComponent()->GetHoldingWeapon().GetObject()->GetClass()->ImplementsInterface(UFirearm::StaticClass()))
	{
		IFirearm* Weapon = Cast<IFirearm>(&*Enemy->GetWeaponHoldingComponent()->GetHoldingWeapon());
		
		if (!Weapon->GetIsEnoughAmmo())
			Enemy->GetReloadingComponent()->Reload();
	}
}
