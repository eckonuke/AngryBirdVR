// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RIM_WidgetInGameFailActor.generated.h"

UCLASS()
class ANGRYBIRDVR_API ARIM_WidgetInGameFailActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARIM_WidgetInGameFailActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


public:
	//위젯 추가
	UPROPERTY(EditAnywhere)
	class UWidgetComponent* widgetInGameFail;


public:
	//WidgetInGameFail 에서 btn_Menu 클릭 했을 때 실행 될 함수
	void GoMenu();

	//WidgetInGameFail 에서 btn_Restart 클릭 했을 때 실행 될 함수
	void GoRestart();

};
