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
	//���� �߰�
	UPROPERTY(EditAnywhere)
	class UWidgetComponent* widgetInGameFail;


public:
	//WidgetInGameFail ���� btn_Menu Ŭ�� ���� �� ���� �� �Լ�
	void GoMenu();

	//WidgetInGameFail ���� btn_Restart Ŭ�� ���� �� ���� �� �Լ�
	void GoRestart();

};
