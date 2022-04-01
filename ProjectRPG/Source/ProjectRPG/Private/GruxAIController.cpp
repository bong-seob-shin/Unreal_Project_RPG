// Fill out your copyright notice in the Description page of Project Settings.


#include "GruxAIController.h"
#include "NavigationSystem.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"

const FName AGruxAIController::StartPosKey(TEXT("StartPos"));
const FName AGruxAIController::PatrolPosKey(TEXT("PatrolPos"));
const FName AGruxAIController::TargetKey(TEXT("Target"));

AGruxAIController::AGruxAIController()
{
	static ConstructorHelpers::FObjectFinder<UBlackboardData> BBObjcet(TEXT("BlackboardData'/Game/PolarWorld/AI/BB_Grux.BB_Grux'"));
	if (BBObjcet.Succeeded())
	{
		BlackboardData = BBObjcet.Object;
	}

	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTObject(TEXT("BehaviorTree'/Game/PolarWorld/AI/BT_Grux.BT_Grux'"));
	if (BTObject.Succeeded())
	{
		BehaviorTree = BTObject.Object;
	}

}

void AGruxAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	if (UseBlackboard(BlackboardData, Blackboard))
	{
		Blackboard->SetValueAsVector(StartPosKey, InPawn->GetActorLocation());
		if (!RunBehaviorTree(BehaviorTree))
			return;
	}
}

void AGruxAIController::OnUnPossess()
{
	Super::OnUnPossess();
}

