// Fill out your copyright notice in the Description page of Project Settings.


#include "BP_Base.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

#include "Camera/CameraComponent.h"

ABP_Base::ABP_Base()
{
	PrimaryActorTick.bCanEverTick = true;
	
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetRootComponent());
	
	PlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
	PlayerCamera->SetupAttachment(CameraBoom);


}

void ABP_Base::BeginPlay()
{
	Super::BeginPlay();

}

void ABP_Base::MoveRight(float DeltaAxis)
{
	if (isAttacking) return;
	if (DeltaAxis > 0.0f)
	{
		BisMovingRight = true;
	}
	else if (DeltaAxis < 0.0f)

	{
			BisMovingRight = false;
	}

	AddMovementInput(FVector(1.0f, 0.0f, 0.0f), DeltaAxis);
}


void ABP_Base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABP_Base::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);


	PlayerInputComponent->BindAxis("MoveRight", this, &ABP_Base::MoveRight);
	PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &ABP_Base::Attack);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ABP_Base::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ABP_Base::StopJumping);
}

void ABP_Base::Attack()
{
	if(isAttacking == false && isTakingDamage == false)
		isAttacking = true;
}

void ABP_Base::HurtPlayer()
{
	FDamageEvent DamageEvent;
	
	TakeDamage(20.0f, DamageEvent, GetController(), GetOwner());
}


float ABP_Base::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	FName Name =  GetController()->GetPawn()->GetFName();
	FString NameString = Name.ToString();
	FString PrintMessage = FString::Printf(TEXT("%s is taking damage of %f"),*NameString, DamageAmount);
	Health -= DamageAmount;
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Green, PrintMessage);
	isTakingDamage = true;
	return DamageAmount;
}

bool IsLeft(FVector Location, FVector MyLocation)
{
	float mX = MyLocation.X;
	float hX = Location.X;

	return mX > hX;

}