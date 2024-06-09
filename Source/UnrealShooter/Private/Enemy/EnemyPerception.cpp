// Copyright Atennop and Krypton. All Rights Reserved.

#include "Enemy/EnemyPerception.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Character/ShooterCharacter.h"

UEnemyPerception::UEnemyPerception()
{
	PrimaryComponentTick.bCanEverTick = true;
}

// ReSharper disable once CppMemberFunctionMayBeConst
// ReSharper disable once CppPassValueParameterByConstReference
void UEnemyPerception::OnPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	if (!Actor->IsA(AShooterCharacter::StaticClass()))
		return;
	
	if (!Stimulus.WasSuccessfullySensed())
	{
		GetWorld()->GetTimerManager().SetTimer(ChasingTimerHandle, [&] { Controller->GetBlackboardComponent()->SetValueAsObject(TargetVariableName, nullptr); }, LoosingTargetTime, false);
		return;
	}
	
	GetWorld()->GetTimerManager().ClearTimer(ChasingTimerHandle);
	Controller->GetBlackboardComponent()->SetValueAsObject(TargetVariableName, Actor);
}

void UEnemyPerception::BeginPlay()
{
	Super::BeginPlay();
	Controller = Cast<AEnemyController>(GetOwner());
	check(IsValid(Controller));
	OnTargetPerceptionUpdated.AddDynamic(this, &UEnemyPerception::OnPerceptionUpdated);
}
