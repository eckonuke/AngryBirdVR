// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RIM_WidgetMain.generated.h"

/**
 * 
 */
UCLASS()
class ANGRYBIRDVR_API URIM_WidgetMain : public UUserWidget
{
	GENERATED_BODY()

public:
	//[SetupPlayerInputComponent] �����Լ�
	void SetupPlayerInputComponent(class UEnhancedInputComponent* PlayerInputComponent);

public:
	//BeginPlay �� ���� ����
	virtual void NativeConstruct() override;

public:
	//[�������Ʈ ������ C++�� ����]
	//��ư
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* btn_PlayStart;


public:
	UPROPERTY()
	class ARIM_WidgetMainActor* widgetMainActor;


public:
	//btn_PlayStart ����
	UFUNCTION()
	void Bind_btn_PlayGame();


};
