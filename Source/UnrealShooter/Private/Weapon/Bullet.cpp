// Copyright Atennop and Krypton. All Rights Reserved.

#include "Weapon/Bullet.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "NiagaraFunctionLibrary.h"

ABullet::ABullet() : BulletLifeTime(), DecalLifeTime()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ABullet::BeginPlay()
{
	Super::BeginPlay();
	check(Collision != nullptr)
	
	GetWorld()->GetTimerManager().SetTimer(DyingTimerHandle, [&] { GetWorld()->DestroyActor(this); }, BulletLifeTime, false);
	Collision->OnComponentHit.AddDynamic(this, &ABullet::OnBulletHit);
}

void ABullet::OnBulletHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	UGameplayStatics::SpawnDecalAttached(DecalMaterial, DecalSize, OtherComp, NAME_None, Hit.Location, UKismetMathLibrary::MakeRotFromX(Hit.Normal), EAttachLocation::KeepWorldPosition, DecalLifeTime);
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), BulletImpactEffect, Hit.Location, UKismetMathLibrary::MakeRotFromX(Hit.Normal));
	
	Collision->OnComponentHit.Clear();
	GetWorld()->GetTimerManager().ClearTimer(DyingTimerHandle);
	GetWorld()->DestroyActor(this);
}
