// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_TurnToTarget.h"
#include "Grux.h"
#include "Kallari.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GruxAIController.h"

UBTTask_TurnToTarget::UBTTask_TurnToTarget()
{
	NodeName = TEXT("Turn");
}


EBTNodeResult::Type UBTTask_TurnToTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	auto Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto AICharacter = Cast<AGrux>(OwnerComp.GetAIOwner()->GetPawn());
	if (AICharacter == nullptr)
		return EBTNodeResult::Failed;

	auto Target = Cast<AKallari>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(AGruxAIController::TargetKey));
	if (Target == nullptr)
		return EBTNodeResult::Failed;


	FVector LookVector = Target->GetActorLocation() - AICharacter->GetActorLocation();
	LookVector.Z = 0.0f;
	FRotator TargetRot = FRotationMatrix::MakeFromX(LookVector).Rotator();

	AICharacter->SetActorRotation(FMath::RInterpTo(AICharacter->GetActorRotation(), TargetRot, GetWorld()->GetDeltaSeconds(), 2.0f));

	return EBTNodeResult::Succeeded;
}
