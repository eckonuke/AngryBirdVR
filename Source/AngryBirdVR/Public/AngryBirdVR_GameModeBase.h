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
	AAngryBirdVR_GameModeBase(); //�߰�

protected:
	virtual void BeginPlay() override; //�߰�

public:
	virtual void Tick(float DeltaTime) override; //�߰�

public:
	//�÷��̾�
	UPROPERTY()
	class ARIM_Player* player;

	//���� ��(����)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 currentPig;

	//���� �ð�
	UPROPERTY()
	float currentTime = 0;


public:
	bool spawnedScreen = false;
};

