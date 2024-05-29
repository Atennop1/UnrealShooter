// Copyright Atennop and Krypton. All Rights Reserved.

#include "Weapon/Bullet.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

ABullet::ABullet(): BulletLifeTime(), DecalLifeTime()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ABullet::BeginPlay()
{
	Super::BeginPlay();
	check(Mesh != nullptr)
	
	GetWorld()->GetTimerManager().SetTimer(DyingTimerHandle, [&] { GetWorld()->DestroyActor(this); }, BulletLifeTime, false);
	Mesh->OnComponentHit.AddDynamic(this, &ABullet::OnBulletHit);
}

void ABullet::OnBulletHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	UGameplayStatics::SpawnDecalAttached(DecalMaterial, DecalSize, OtherComp, NAME_None, Hit.Location,
		UKismetMathLibrary::MakeRotFromX(Hit.Normal), EAttachLocation::KeepWorldPosition, DecalLifeTime);
	
	Mesh->OnComponentHit.Clear();
	GetWorld()->GetTimerManager().ClearTimer(DyingTimerHandle);
	GetWorld()->DestroyActor(this);
}
