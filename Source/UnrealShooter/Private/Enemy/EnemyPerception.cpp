// Copyright Atennop and Krypton. All Rights Reserved.

#include "Enemy/EnemyPerception.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Character/ShooterCharacter.h"
#include "Perception/AISense_Prediction.h"

UEnemyPerception::UEnemyPerception()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UEnemyPerception::BeginPlay()
{
	Super::BeginPlay();
	Controller = Cast<AEnemyController>(GetOwner());
	check(IsValid(Controller));
	OnTargetPerceptionUpdated.AddDynamic(this, &UEnemyPerception::OnPerceptionUpdated);
}

// ReSharper disable once CppMemberFunctionMayBeConst
// ReSharper disable once CppPassValueParameterByConstReference
void UEnemyPerception::OnPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	SensedActor = Actor;
	if (!SensedActor->IsA(AShooterCharacter::StaticClass()))
		return;

	if (Stimulus.Type.Name == "Default__AISense_Prediction")
		Controller->GetBlackboardComponent()->SetValueAsVector(PredictionLocationVariableName, Stimulus.StimulusLocation);
	
	if (Stimulus.Type.Name == "Default__AISense_Hearing")
	{
		Controller->GetBlackboardComponent()->SetValueAsBool(IsHearingPlayerVariableName, Stimulus.WasSuccessfullySensed());
		
		if (Stimulus.WasSuccessfullySensed())
			Controller->GetBlackboardComponent()->SetValueAsVector(NoiseLocationVariableName, Stimulus.StimulusLocation);
	}
	
	if (Stimulus.Type.Name == "Default__AISense_Sight" || Stimulus.Type.Name == "Default__AISense_Damage")
	{
		Controller->GetBlackboardComponent()->SetValueAsBool(CanSeePlayerVariableName, Stimulus.WasSuccessfullySensed());
		
		if (Stimulus.WasSuccessfullySensed())
		{
			GetWorld()->GetTimerManager().ClearTimer(ChasingTimerHandle);
			Controller->GetBlackboardComponent()->SetValueAsObject(TargetVariableName, SensedActor);
			return;
		}
		
		GetWorld()->GetTimerManager().SetTimer(ChasingTimerHandle, [&] { Controller->GetBlackboardComponent()->SetValueAsObject(TargetVariableName, nullptr); }, LoosingTargetTime, false);
		UAISense_Prediction::RequestControllerPredictionEvent(Controller, SensedActor, 1);
	}
}
