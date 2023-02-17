// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RIM_WidgetStageSelect.generated.h"

/**
 * 
 */
UCLASS()
class ANGRYBIRDVR_API URIM_WidgetStageSelect : public UUserWidget
{
	GENERATED_BODY()
	
public:
	//[SetupPlayerInputComponent] 가상함수
	void SetupPlayerInputComponent(class UEnhancedInputComponent* PlayerInputComponent);

public:
	//BeginPlay 와 같은 동작
	virtual void NativeConstruct() override;

	//[블루프린트 위젯을 C++과 연결]
	//버튼
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* btn_Stage01;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* btn_Stage02;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* btn_Stage03;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* btn_Stage04;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* btn_Stage05;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* btn_Back;


public:
	UPROPERTY()
	class ARIM_WidgetStageSelectActor* widgetStageSelectActor;


public:
	//btn_Stage01 연결
	UFUNCTION()
	void Bind_btn_PlayStage01();

	//btn_Stage02 연결
	UFUNCTION()
	void Bind_btn_PlayStage02();

	//btn_Stage03 연결
	UFUNCTION()
	void Bind_btn_PlayStage03();

	//btn_Stage04 연결
	UFUNCTION()
	void Bind_btn_PlayStage04();

	//btn_Stage05 연결
	UFUNCTION()
	void Bind_btn_PlayStage05();

	//btn_GoBack 연결
	UFUNCTION()
	void Bind_btn_GoBack();



};
