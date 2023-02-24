// Fill out your copyright notice in the Description page of Project Settings.


#include "AngryBirdVR_GameModeBase.h"
#include <Kismet/GameplayStatics.h>
#include "RIM_WidgetInGameScoreActor.h"
#include "RIM_Player.h"
#include "RIM_Pig.h"
#include "RIM_WidgetInGameFailActor.h"
#include "RIM_MoveComponent.h"

AAngryBirdVR_GameModeBase::AAngryBirdVR_GameModeBase() //�߰�
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


}

void AAngryBirdVR_GameModeBase::BeginPlay() //�߰� 
{
	Super::BeginPlay();
	player = Cast<ARIM_Player>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	TArray<AActor*> tempArray;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ARIM_Pig::StaticClass(), tempArray);
	currentPig = tempArray.Num();
}

void AAngryBirdVR_GameModeBase::Tick(float DeltaTime) //�߰�
{
	Super::Tick(DeltaTime);
}