// Copyright Atennop and Krypton. All Rights Reserved.

#include "Weapon/Bullet.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "NiagaraFunctionLibrary.h"
#include "Character/Health/IHealth.h"

ABullet::ABullet() : BulletLifeTime(), Damage(), DecalLifeTime()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ABullet::BeginPlay()
{
	Super::BeginPlay();
	check(Collision != nullptr)
	
	SetLifeSpan(BulletLifeTime);
	Collision->OnComponentHit.AddDynamic(this, &ABullet::OnBulletHit);
}

void ABullet::OnBulletHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherComp->Implements<UHealth>())
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), BloodEffect, Hit.Location, UKismetMathLibrary::MakeRotFromX(Hit.Normal), FVector::One());
		Cast<IHealth>(OtherComp)->Damage(Damage);
	}
	else
	{
		UGameplayStatics::SpawnDecalAttached(DecalMaterial, DecalSize, OtherComp, NAME_None, Hit.Location, UKismetMathLibrary::MakeRotFromX(Hit.Normal), EAttachLocation::KeepWorldPosition, DecalLifeTime);
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), BulletImpactEffect, Hit.Location, UKismetMathLibrary::MakeRotFromX(Hit.Normal));
	}
	
	Collision->OnComponentHit.Clear();
	GetWorld()->DestroyActor(this);
}
