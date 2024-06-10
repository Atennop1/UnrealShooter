// Copyright Atennop and Krypton. All Rights Reserved.

#include "Enemy/BT/ShootingService.h"
#include "AIController.h"
#include "Character/ShooterCharacter.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Weapon/Interfaces/IFirearm.h"

UShootingService::UShootingService()
{
	NodeName = TEXT("Shooting Service");
}

void UShootingService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	const AAIController *Controller = OwnerComp.GetAIOwner();
	AShooterCharacter *Enemy = Cast<AShooterCharacter>(Controller->GetPawn());

	if (!IsValid(Controller->GetFocusActor()))
		return;
	
	FHitResult HitResult;
	TArray<AActor*> ActorsToIgnore = TArray<AActor*> { Enemy };

	if (Enemy->GetWeaponHoldingComponent()->GetIsHolding())
		ActorsToIgnore.Add(Cast<AActor>(Enemy->GetWeaponHoldingComponent()->GetHoldingWeapon().GetObject()));
	
	const bool WasHit = UKismetSystemLibrary::SphereTraceSingle(GetWorld(), Enemy->GetActorLocation(), Controller->GetFocusActor()->GetActorLocation(), CheckSphereRadius, TraceTypeQuery2, false, ActorsToIgnore, EDrawDebugTrace::None, HitResult, true);
	if (!WasHit || Controller->GetFocusActor() != HitResult.GetActor())
	{
		Enemy->GetShootingComponent()->StopShooting();
		Enemy->GetAimingComponent()->StopAim();
		return;
	}
	
	if (Enemy->GetWeaponHoldingComponent()->GetIsHolding() && Enemy->GetWeaponHoldingComponent()->GetHoldingWeapon().GetObject()->GetClass()->ImplementsInterface(UFirearm::StaticClass()))
	{
		IFirearm* Weapon = Cast<IFirearm>(&*Enemy->GetWeaponHoldingComponent()->GetHoldingWeapon());
		if (!Weapon->GetIsEnoughAmmo())
		{
			Enemy->GetReloadingComponent()->Reload();
			return;
		}
		
		Enemy->GetAimingComponent()->StartAim();
		Enemy->GetShootingComponent()->StartShooting();
		
		if (Weapon->GetData().WeaponFiringType == EWeaponFiringType::Tapping)
			Enemy->GetShootingComponent()->StopShooting();
	}
}
