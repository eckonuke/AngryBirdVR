// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RIM_WidgetStageSelectActor.generated.h"

UCLASS()
class ANGRYBIRDVR_API ARIM_WidgetStageSelectActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARIM_WidgetStageSelectActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


public:
	//���� �߰�
	UPROPERTY(EditAnywhere)
	class UWidgetComponent* widgetStageSelect;


public:
	//WidgetStageSelect ���� btn_Stage01 Ŭ�� ���� �� ���� �� �Լ�
	void PlayStage01();

	//WidgetStageSelect ���� btn_Stage02 Ŭ�� ���� �� ���� �� �Լ�
	void PlayStage02();

	//WidgetStageSelect ���� btn_Stage03 Ŭ�� ���� �� ���� �� �Լ�
	void PlayStage03();

	//WidgetStageSelect ���� btn_Stage04 Ŭ�� ���� �� ���� �� �Լ�
	void PlayStage04();

	//WidgetStageSelect ���� btn_Stage05 Ŭ�� ���� �� ���� �� �Լ�
	void PlayStage05();

	//WidgetStageSelect ���� btn_GoBack Ŭ�� ���� �� ���� �� �Լ�
	void GoBack();


};
