// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Attack.h"
#include "Grux.h"
#include "GruxAIController.h"

UBTTask_Attack::UBTTask_Attack()
{
	bNotifyTick = true;
	bIsAttacking = false;
}
EBTNodeResult::Type UBTTask_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto Grux = Cast<AGrux>(OwnerComp.GetAIOwner()->GetPawn());
	if (Grux == nullptr)
		return EBTNodeResult::Failed;

	Grux->Attack();
	bIsAttacking = true;
	Grux->OnAttackEnd.AddLambda([this]() {
		bIsAttacking = false;
		});

	return EBTNodeResult::InProgress;
}

void UBTTask_Attack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
	if(!bIsAttacking)
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
}


