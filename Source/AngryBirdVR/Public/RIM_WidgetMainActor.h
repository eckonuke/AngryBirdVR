// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RIM_WidgetMainActor.generated.h"

UCLASS()
class ANGRYBIRDVR_API ARIM_WidgetMainActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARIM_WidgetMainActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


public:
	//���� �߰�
	UPROPERTY(EditAnywhere)
		class UWidgetComponent* widgetMain;


public:
	//WidgetMain ���� btn_PlayGame Ŭ�� ���� �� ���� �� �Լ�
	void PlayGame();


};
