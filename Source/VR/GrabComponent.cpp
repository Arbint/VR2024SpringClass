// Fill out your copyright notice in the Description page of Project Settings.


#include "GrabComponent.h"

// Sets default values for this component's properties
UGrabComponent::UGrabComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UGrabComponent::Grab(USceneComponent* GrabingComponent)
{
	if (OwnerRootAsPrimitive && bIsOwnerDynamic)
	{
		OwnerRootAsPrimitive->SetSimulatePhysics(false);
	}
	OwnerRoot->AttachToComponent(GrabingComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
}

void UGrabComponent::Release()
{
	OwnerRoot->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
	if (OwnerRootAsPrimitive && bIsOwnerDynamic)
	{
		OwnerRootAsPrimitive->SetSimulatePhysics(true);
	}
}


// Called when the game starts
void UGrabComponent::BeginPlay()
{
	Super::BeginPlay();

	OwnerRoot = GetOwner()->GetRootComponent();
	OwnerRootAsPrimitive = Cast<UPrimitiveComponent>(OwnerRoot);
	if (OwnerRootAsPrimitive)
	{
		bIsOwnerDynamic = OwnerRootAsPrimitive->IsSimulatingPhysics();
	}
	// ...
}


// Called every frame
void UGrabComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

