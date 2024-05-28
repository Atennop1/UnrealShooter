// Copyright Atennop and Krypton. All Rights Reserved.

#include "Weapon/Bullet.h"

ABullet::ABullet()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ABullet::BeginPlay()
{
	Super::BeginPlay();
	check(Mesh != nullptr)
	
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, [&] { GetWorld()->DestroyActor(this); }, 3, false);
	Mesh->OnComponentHit.AddDynamic(this, &ABullet::OnBulletHit);
}

void ABullet::OnBulletHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	Mesh->OnComponentHit.Clear();
	GetWorld()->DestroyActor(this);
}
