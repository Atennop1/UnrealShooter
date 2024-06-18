// Copyright Atennop. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CharacterDyingComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class UNREALSHOOTER_API UCharacterDyingComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	UPROPERTY()
	class AShooterCharacter *Character = nullptr;

	UPROPERTY(BlueprintReadWrite, meta=(AllowPrivateAccess))
	USceneComponent *ComponentToAttachCamera = nullptr;

	UPROPERTY(EditDefaultsOnly)
	float DyingTime = 5;
	FTimerHandle DyingTimerHandle;

	UPROPERTY(EditDefaultsOnly)
	FTransform CameraTransformAfterDeath;

	UPROPERTY(EditDefaultsOnly)
	UUserWidget* DeathScreen = nullptr;

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
	UCharacterDyingComponent();
	void Die();
};
