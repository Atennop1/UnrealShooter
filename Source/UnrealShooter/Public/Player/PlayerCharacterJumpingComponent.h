// Copyright Atennop and Krypton. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Character/Movement/ICharacterJumpingComponent.h"
#include "Components/ActorComponent.h"
#include "PlayerCharacterJumpingComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class UNREALSHOOTER_API UPlayerCharacterJumpingComponent : public UActorComponent, public ICharacterJumpingComponent
{
	GENERATED_BODY()

private:
	UPROPERTY()
	class AShooterCharacter *Character = nullptr;
	
protected:
	virtual void BeginPlay() override;

public:
	UPlayerCharacterJumpingComponent();

	virtual void StartJumping() override;
	virtual void StopJumping() override;
};
