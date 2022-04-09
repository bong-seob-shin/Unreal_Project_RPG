// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_DetectTarget.h"
#include "GruxAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "DrawDebugHelpers.h"
#include "Kallari.h"

UBTService_DetectTarget::UBTService_DetectTarget()
{
	NodeName = TEXT("DetectTarget");
	Interval = 1.0f;
	DetectRadius = 1000.0f;
}

void UBTService_DetectTarget::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (ControllingPawn == nullptr)
		return;

	UWorld* World = ControllingPawn->GetWorld();
	FVector Center = ControllingPawn->GetActorLocation();
	
	if (World == nullptr)
		return;

	TArray<FOverlapResult> OverlapResults;
	FCollisionQueryParams CollisionParams(NAME_None, false, ControllingPawn);
	bool bResult = World->OverlapMultiByChannel(
		OverlapResults,
		Center,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel4,
		FCollisionShape::MakeSphere(DetectRadius),
		CollisionParams
	);


	if (bResult)
	{
		for (auto const& OverlapResult : OverlapResults)
		{
			AKallari* const Character = Cast<AKallari>(OverlapResult.GetActor());
			if (Character != nullptr && Character->GetController()->IsPlayerController() &&!Character->GetIsHiding()) //this CrossCheck increase accuracy
			{
				OwnerComp.GetBlackboardComponent()->SetValueAsObject(AGruxAIController::TargetKey, Character);
				//DrawDebugSphere(World, Center, DetectRadius, 16, FColor::Green, false, 0.2f);

				//DrawDebugPoint(World, Character->GetActorLocation(), 10.0f, FColor::Blue, false, 0.2f);

				//DrawDebugLine(World, ControllingPawn->GetActorLocation(),Character->GetActorLocation(), FColor::Blue, false, 0.2f);
				
				return;
			}
		}
	}
	OwnerComp.GetBlackboardComponent()->SetValueAsObject(AGruxAIController::TargetKey, nullptr);

	//DrawDebugSphere(World, Center, DetectRadius, 16, FColor::Red, false, 0.2f);
}

