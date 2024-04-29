// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "VRCharacter.generated.h"

UCLASS()
class VR_API AVRCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AVRCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
private:
	void Move(const FInputActionValue& InputActionVal);

	void Turn(const FInputActionValue& InputActionVal);

	void GrabActionTriggered(const FInputActionValue& InputActionVal);
	
	void StartTeleport();
	void TeleportTargetting();
	void CommitTeleport();

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	float TurnSpeed = 5.f;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* GrabInputAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputMappingContext* InputMappingContext;
	
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* MoveInputAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* TurnInputAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* TeleportAction;

	UPROPERTY(VisibleDefaultsOnly, Category = "Camera")
	class UCameraComponent* ViewCam;

	UPROPERTY(VisibleDefaultsOnly, Category = "VR")
	class UVMotionControllerComponent* LeftHandControllerComp;

	UPROPERTY(VisibleDefaultsOnly, Category = "VR")
	class UVMotionControllerComponent* RightHandControllerComp;

	UPROPERTY(VisibleDefaultsOnly, Category = "VR")
	class UVMotionControllerComponent* LeftAimControllerComp;

	UPROPERTY(VisibleDefaultsOnly, Category = "VR")
	class UVMotionControllerComponent* RightAimControllerComp;

	UPROPERTY(VisibleDefaultsOnly, Category = "VR")
	class USkeletalMeshComponent* RightHandMesh;

	UPROPERTY(VisibleDefaultsOnly, Category = "VR")
	class USkeletalMeshComponent* LeftHandMesh;

	void PrintMsgOnScreen(const FString& Msg);
};
