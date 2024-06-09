// Copyright Atennop and Krypton. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Character/Movement/ICharacterMovingComponent.h"
#include "Components/ActorComponent.h"
#include "PlayerCharacterMovingComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class UNREALSHOOTER_API UPlayerCharacterMovingComponent : public UActorComponent, public ICharacterMovingComponent
{
	GENERATED_BODY()

private:
	UPROPERTY()
	class AShooterCharacter *Character = nullptr;

protected:
	virtual void BeginPlay() override;
	
public:
	UPlayerCharacterMovingComponent();
	virtual void Move(const FVector2D Input) override;
};
