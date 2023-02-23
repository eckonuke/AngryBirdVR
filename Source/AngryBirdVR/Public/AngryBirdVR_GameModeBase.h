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

	//TArray ����
	UPROPERTY()
	TArray <class AActor*> pig;

	//���� ��(����)
	UPROPERTY()
	class ARIM_Pig* currentPig;

	//���� �ð�
	UPROPERTY()
	float currentTime = 0;


public:
	//��(����)�� �� �׾����� üũ
	void FindEnemyActor();
	
	//��(����) ���� Ȯ�� ����
	bool EnemyAllDie = false; //True �̸� �� ����
	bool spawnedScreen = false;
};

