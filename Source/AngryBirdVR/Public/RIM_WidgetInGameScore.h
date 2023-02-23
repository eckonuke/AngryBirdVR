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

	//��
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* Score;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class ARIM_Player* player;

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

public:
	//[�� ����]
// 	UFUNCTION()
// 	void Bind_Star1();
// 
// 	UFUNCTION()
// 	void Bind_Star2();
// 
// 	UFUNCTION()
// 	void Bind_Star3();

private:
	UFUNCTION()
	void starCalc(int32 point);
	UFUNCTION()
	void Init();
	float targetScore = 0;
};
