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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* btn_Next;

	//별
// 	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
// 	class UImage* img_Star1;
// 
// 	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
// 	class UImage* img_Star2;
// 
// 	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
// 	class UImage* img_Star3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UImage* img_Star_Yellow1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UImage* img_Star_Yellow2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UImage* img_Star_Yellow3;

public:
	UPROPERTY()
	class ARIM_WidgetInGameScoreActor* widgetInGameScoreActor;


public:
	//btn_Menu 연결
	UFUNCTION()
	void Bind_btn_GoMenu();

	//btn_Restart 연결
	UFUNCTION()
	void Bind_btn_GoRestart();

	//btn_Next 연결
	UFUNCTION()
	void Bind_btn_GoNext();

public:
	//[별 연결]
// 	UFUNCTION()
// 	void Bind_Star1();
// 
// 	UFUNCTION()
// 	void Bind_Star2();
// 
// 	UFUNCTION()
// 	void Bind_Star3();

	UFUNCTION()
	void Bind_Star_Yellow1();

	UFUNCTION()
	void Bind_Star_Yellow2();

	UFUNCTION()
	void Bind_Star_Yellow3();


};
