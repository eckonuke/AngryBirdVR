// Fill out your copyright notice in the Description page of Project Settings.


#include "RIM_Enemy.h"

// Sets default values
ARIM_Enemy::ARIM_Enemy()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ARIM_Enemy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARIM_Enemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ARIM_Enemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

