// Copyright Atennop and Krypton. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "Components/ActorComponent.h"
#include "ShooterCharacterMovingComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class UNREALSHOOTER_API UShooterCharacterMovingComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	UPROPERTY()
	class AShooterCharacter *Character = nullptr;

protected:
	virtual void BeginPlay() override;
	
public:
	UShooterCharacterMovingComponent();
	void Move(const FVector2D Input) const;
	void Rotate(const FVector2D Input) const;
};
