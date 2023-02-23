// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RIM_WidgetInGameFail.generated.h"

/**
 * 
 */
UCLASS()
class ANGRYBIRDVR_API URIM_WidgetInGameFail : public UUserWidget
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
	class UButton* btn_Menu;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* btn_Restart;


public:
	UPROPERTY()
	class ARIM_WidgetInGameFailActor* widgetInGameFailActor;


public:
	//btn_Menu ����
	UFUNCTION()
	void Bind_btn_GoMenu();

	//btn_Restart ����
	UFUNCTION()
	void Bind_btn_GoRestart();

};
