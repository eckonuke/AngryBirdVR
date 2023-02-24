// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "AngryBirdVR_GameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class ANGRYBIRDVR_API AAngryBirdVR_GameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	AAngryBirdVR_GameModeBase(); //추가

protected:
	virtual void BeginPlay() override; //추가

public:
	virtual void Tick(float DeltaTime) override; //추가

public:
	//플레이어
	UPROPERTY()
	class ARIM_Player* player;

	//현재 적(돼지)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 currentPig;

	//현재 시간
	UPROPERTY()
	float currentTime = 0;


public:
	bool spawnedScreen = false;
};

