// Copyright Atennop and Krypton. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ShooterCharacterMovementComponent.h"
#include "GameFramework/Character.h"
#include "ShooterCharacter.generated.h"

UCLASS()
class UNREALSHOOTER_API AShooterCharacter : public ACharacter
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta=(AllowPrivateAccess=true))
	UShooterCharacterMovementComponent *MovementComponent = nullptr;

protected:
	virtual void BeginPlay() override;
	
public:
	AShooterCharacter();
	void Move(const FVector2D Input) const { MovementComponent->Move(Input); }
	void Look(const FVector2D Input) const { MovementComponent->Look(Input); }
};
