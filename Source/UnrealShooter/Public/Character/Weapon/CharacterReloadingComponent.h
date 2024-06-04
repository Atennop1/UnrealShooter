// Copyright Atennop and Krypton. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CharacterReloadingComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class UNREALSHOOTER_API UCharacterReloadingComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly)
	TMap<UClass*, UClass*> WeaponsToMagazines;

	UPROPERTY(EditDefaultsOnly)
	TMap<UClass*, FName> WeaponsToHidingBones;

	UPROPERTY(EditDefaultsOnly)
	TMap<UClass*, FName> WeaponsToMagazineSockets;
	
	UPROPERTY()
	class AShooterCharacter *Character = nullptr;

	UPROPERTY()
	USkeletalMeshComponent *CharacterMesh = nullptr;
	
	UPROPERTY()
	USkeletalMeshComponent *WeaponMesh = nullptr;

	UPROPERTY()
	AActor *OldMagazine = nullptr;

	UPROPERTY()
	AActor *NewMagazine = nullptr;

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	UCharacterReloadingComponent();
	void Reload();

	UFUNCTION(BlueprintCallable)
	bool IsReloading() const;

	UFUNCTION(BlueprintCallable)
	void RemoveMagazine();

	UFUNCTION(BlueprintCallable)
	void DropMagazine() const;

	UFUNCTION(BlueprintCallable)
	void TakeMagazine();

	UFUNCTION(BlueprintCallable)
	void PlaceMagazine();
};
