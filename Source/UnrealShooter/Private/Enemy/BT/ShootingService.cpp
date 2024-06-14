// Copyright Atennop and Krypton. All Rights Reserved.

#include "Enemy/BT/ShootingService.h"
#include "AIController.h"
#include "Enemy/EnemyCharacter.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Weapon/Interfaces/IFirearm.h"

UShootingService::UShootingService()
{
	NodeName = TEXT("Shooting Service");
}

void UShootingService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	const AAIController *Controller = OwnerComp.GetAIOwner();
	AEnemyCharacter *Enemy = Cast<AEnemyCharacter>(Controller->GetPawn());

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
		Enemy->GetAimingComponent()->StartAim();
		Enemy->GetShootingComponent()->StartShooting();

		if (IFirearm* Weapon = Cast<IFirearm>(&*Enemy->GetWeaponHoldingComponent()->GetHoldingWeapon()); Weapon->GetData().WeaponFiringType == EWeaponFiringType::Tapping)
			Enemy->GetShootingComponent()->StopShooting();
	}
}
