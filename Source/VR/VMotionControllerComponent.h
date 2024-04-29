// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MotionControllerComponent.h"
#include "Kismet/GameplayStaticsTypes.h"
#include "VMotionControllerComponent.generated.h"

/**
 * 
 */
UCLASS()
class VR_API UVMotionControllerComponent : public UMotionControllerComponent
{
	GENERATED_BODY()
public:
	void StartTracing();
	void DoTracing();
	FHitResult StopGetTracingResult() const;
	virtual void BeginPlay() override;
	void TryGrab();
	void Release();
private:
	UPROPERTY(EditDefaultsOnly, Category = "Trace")
	float TraceProjectileLaunchVelocity = 500.f;

	UPROPERTY(EditDefaultsOnly, Category = "Trace")
	float TraceProjectileRadius = 30.f;

	FPredictProjectilePathResult TraceResult;

	UPROPERTY()
	class UNiagaraComponent* TraceComp;

	UPROPERTY(EditDefaultsOnly, Category = "VFX")
	class UNiagaraSystem* TraceSystemAsset;

	class UGrabComponent* CurrentlyGrabingComp;
};