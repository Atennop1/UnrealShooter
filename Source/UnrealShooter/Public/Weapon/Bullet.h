// Copyright Atennop and Krypton. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bullet.generated.h"

UCLASS()
class UNREALSHOOTER_API ABullet : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(BlueprintReadWrite, meta=(AllowPrivateAccess))
	UMeshComponent *Mesh = nullptr;

	UPROPERTY(EditDefaultsOnly)
	float BulletLifeTime;
	FTimerHandle DyingTimerHandle;

	UPROPERTY(EditDefaultsOnly)
	float DecalLifeTime;
	
	UPROPERTY(EditDefaultsOnly)
	FVector DecalSize;
	
	UPROPERTY(EditDefaultsOnly)
	UMaterialInterface *DecalMaterial = nullptr;
	
protected:
	virtual void BeginPlay() override;

	UFUNCTION() 
	void OnBulletHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	
public:
	ABullet();
};
