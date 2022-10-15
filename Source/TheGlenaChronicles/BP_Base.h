// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraComponent.h"
#include "BP_Base.generated.h"

/**
 * 
 */
UCLASS()
class THEGLENACHRONICLES_API ABP_Base : public APaperCharacter
{
	GENERATED_BODY()
	
public:
	// Sets default values for this character's properties
	ABP_Base();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	void MoveRight(float DeltaAxis);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	void Attack();

	UFUNCTION(BlueprintCallable)
		void HurtPlayer();


	virtual float TakeDamage
	(
		float DamageAmount,
		struct FDamageEvent const& DamageEvent,
		class AController* EventInstigator,
		AActor* DamageCauser
	) override;

public:

	UPROPERTY(BlueprintReadWrite)
		bool BisMovingRight = true;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		bool isAttacking;

	UPROPERTY(BlueprintReadWrite)
		bool isTakingDamage;

	UPROPERTY(BlueprintReadWrite)
		bool isMoving;

	UPROPERTY(BlueprintReadWrite)
		bool isJumping;

	UPROPERTY(BlueprintReadWrite)
		bool isHurtingPlayer;

	UPROPERTY(BlueprintReadWrite)
		bool isAI;

	UPROPERTY(EditDefaultsOnly)
		USpringArmComponent* CameraBoom;
	
	UPROPERTY(EditDefaultsOnly)
		UCameraComponent* PlayerCamera;

private:
	APlayerController* Controller;

	FRotator RightRotation = FRotator(0.0f, 0.0f, 0.0f);
	FRotator LeftRotation = FRotator(0.0f, 0.0f, 180.0f);

	float Health = 100.0f;


};