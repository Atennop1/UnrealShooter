// Copyright Atennop and Krypton. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CharacterSpeedSetterComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class UNREALSHOOTER_API UCharacterSpeedSetterComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	UPROPERTY()
	class AShooterCharacter *Character = nullptr;

	UPROPERTY(EditDefaultsOnly)
	float WalkSpeed = 600;

	UPROPERTY(EditDefaultsOnly)
	float CrouchSpeed = 300;

	UPROPERTY(EditDefaultsOnly)
	float AimSpeed = 350;
	
protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,  FActorComponentTickFunction* ThisTickFunction) override;

public:
	UCharacterSpeedSetterComponent();
};
