// Copyright Atennop and Krypton. All Rights Reserved.

#include "Enemy/BT/ReloadingService.h"
#include "AIController.h"
#include "Character/ShooterCharacter.h"
#include "Weapon/Interfaces/IFirearm.h"

UReloadingService::UReloadingService()
{
	NodeName = TEXT("Reloading Service");
}

void UReloadingService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	const AShooterCharacter *Enemy = Cast<AShooterCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	
	if (Enemy->GetWeaponHoldingComponent()->GetIsHolding() && Enemy->GetWeaponHoldingComponent()->GetHoldingWeapon().GetObject()->GetClass()->ImplementsInterface(UFirearm::StaticClass()))
	{
		IFirearm* Weapon = Cast<IFirearm>(&*Enemy->GetWeaponHoldingComponent()->GetHoldingWeapon());
		
		if (!Weapon->GetIsEnoughAmmo())
			Enemy->GetReloadingComponent()->Reload();
	}
}
