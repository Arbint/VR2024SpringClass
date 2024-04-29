// Fill out your copyright notice in the Description page of Project Settings.
#include "VMotionControllerComponent.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraSystem.h"
#include "NiagaraComponent.h"
#include "NiagaraDataInterfaceArrayFunctionLibrary.h"
#include "NavigationSystem.h"
#include "GrabComponent.h"

void UVMotionControllerComponent::StartTracing()
{
	TraceComp->SetVisibility(true);
}

void UVMotionControllerComponent::DoTracing()
{
	FPredictProjectilePathParams PathParams;
	PathParams.ActorsToIgnore.Add(GetOwner());
	PathParams.bTraceWithChannel = true;
	PathParams.TraceChannel = ECC_Visibility;
	//PathParams.DrawDebugType = EDrawDebugTrace::ForOneFrame;
	PathParams.StartLocation = GetComponentLocation();
	PathParams.LaunchVelocity = GetForwardVector() * TraceProjectileLaunchVelocity;
	PathParams.bTraceWithCollision = true;
	PathParams.ProjectileRadius = TraceProjectileRadius;

	UGameplayStatics::PredictProjectilePath(this, PathParams, TraceResult);

	if (TraceResult.HitResult.bBlockingHit)
	{
		FNavLocation ProjectedNavMeshLocation;
		if (UNavigationSystemV1::GetNavigationSystem(this)->ProjectPointToNavigation(TraceResult.HitResult.ImpactPoint, ProjectedNavMeshLocation))
		{
			TraceResult.HitResult.ImpactPoint = FVector(ProjectedNavMeshLocation);
		}
		else
		{
			TraceResult.HitResult.bBlockingHit = false;
		}
	}
	TArray<FVector> Positions;
	for (const FPredictProjectilePathPointData& Pos : TraceResult.PathData)
	{
		Positions.Add(Pos.Location);
	}

	Positions.Add(TraceResult.HitResult.ImpactPoint);

	UNiagaraDataInterfaceArrayFunctionLibrary::SetNiagaraArrayVector(TraceComp, "RibbonPositions", Positions);
	TraceComp->SetVectorParameter("EndPosition", TraceResult.HitResult.ImpactPoint);
}

FHitResult UVMotionControllerComponent::StopGetTracingResult() const
{
	TraceComp->SetVisibility(false);
	return TraceResult.HitResult;
}

void UVMotionControllerComponent::BeginPlay()
{
	Super::BeginPlay();
	TraceComp = NewObject<UNiagaraComponent>(GetOwner(), NAME_None);
	TraceComp->SetAsset(TraceSystemAsset);
	TraceComp->SetupAttachment(this);
	TraceComp->RegisterComponent();
	TraceComp->SetVisibility(false);
}

void UVMotionControllerComponent::TryGrab()
{
	TArray<FOverlapResult> Results;
	FCollisionShape ColShape;
	ColShape.SetSphere(100.f);
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(GetOwner());
	if (GetWorld()->OverlapMultiByChannel(Results, GetComponentLocation(), FQuat::Identity, ECC_Visibility, ColShape, Params))
	{
		for (const FOverlapResult& Result : Results)
		{
			AActor* Actor = Result.GetActor();
			UGrabComponent* GrabComp = Actor->FindComponentByClass<UGrabComponent>();
			if (GrabComp)
			{
				GrabComp->Grab(this);
				CurrentlyGrabingComp = GrabComp;
				return;
			}
		}
	}
}

void UVMotionControllerComponent::Release()
{
	if (CurrentlyGrabingComp)
	{
		CurrentlyGrabingComp->Release();
	}
}
