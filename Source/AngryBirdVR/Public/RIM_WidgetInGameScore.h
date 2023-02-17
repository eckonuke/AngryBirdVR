// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RIM_WidgetInGameScore.generated.h"

/**
 * 
 */
UCLASS()
class ANGRYBIRDVR_API URIM_WidgetInGameScore : public UUserWidget
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* btn_Next;


public:
	UPROPERTY()
	class ARIM_WidgetInGameScoreActor* widgetInGameScoreActor;


public:
	//btn_Menu ����
	UFUNCTION()
	void Bind_btn_GoMenu();

	//btn_Restart ����
	UFUNCTION()
	void Bind_btn_GoRestart();

	//btn_Next ����
	UFUNCTION()
	void Bind_btn_GoNext();


};
