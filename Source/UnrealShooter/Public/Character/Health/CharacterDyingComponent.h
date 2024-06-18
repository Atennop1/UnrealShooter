// Copyright Atennop and Krypton. All Rights Reserved.

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
	float TimeForMeshToDisappear = 5;

	UPROPERTY(EditDefaultsOnly)
	FTransform CameraTransformAfterDeath;

	UPROPERTY(EditDefaultsOnly)
	UUserWidget* DeathScreen = nullptr;

protected:
	virtual void BeginPlay() override;

public:
	UCharacterDyingComponent();
	void Die() const;
};
