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
	//[SetupPlayerInputComponent] 가상함수
	void SetupPlayerInputComponent(class UEnhancedInputComponent* PlayerInputComponent);

public:
	//BeginPlay 와 같은 동작
	virtual void NativeConstruct() override;

public:
	//[블루프린트 위젯을 C++과 연결]
	//버튼
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* btn_Menu;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* btn_Restart;


public:
	UPROPERTY()
	class ARIM_WidgetInGameFailActor* widgetInGameFailActor;


public:
	//btn_Menu 연결
	UFUNCTION()
	void Bind_btn_GoMenu();

	//btn_Restart 연결
	UFUNCTION()
	void Bind_btn_GoRestart();

};
