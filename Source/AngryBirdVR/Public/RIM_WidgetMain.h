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
	//[SetupPlayerInputComponent] 가상함수
	void SetupPlayerInputComponent(class UEnhancedInputComponent* PlayerInputComponent);

public:
	//BeginPlay 와 같은 동작
	virtual void NativeConstruct() override;

public:
	//[블루프린트 위젯을 C++과 연결]
	//버튼
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* btn_PlayStart;


public:
	UPROPERTY()
	class ARIM_WidgetMainActor* widgetMainActor;


public:
	//btn_PlayStart 연결
	UFUNCTION()
	void Bind_btn_PlayGame();


};
