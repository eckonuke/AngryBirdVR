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
	//위젯 추가
	UPROPERTY(EditAnywhere)
	class UWidgetComponent* widgetStageSelect;


public:
	//WidgetStageSelect 에서 btn_Stage01 클릭 했을 때 실행 될 함수
	void PlayStage01();

	//WidgetStageSelect 에서 btn_Stage02 클릭 했을 때 실행 될 함수
	void PlayStage02();

	//WidgetStageSelect 에서 btn_Stage03 클릭 했을 때 실행 될 함수
	void PlayStage03();

	//WidgetStageSelect 에서 btn_Stage04 클릭 했을 때 실행 될 함수
	void PlayStage04();

	//WidgetStageSelect 에서 btn_Stage05 클릭 했을 때 실행 될 함수
	void PlayStage05();

	//WidgetStageSelect 에서 btn_GoBack 클릭 했을 때 실행 될 함수
	void GoBack();


};
