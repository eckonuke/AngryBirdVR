// Fill out your copyright notice in the Description page of Project Settings.


#include "RIM_WidgetStageSelect.h"
#include <Kismet/GameplayStatics.h>
#include "Components/Button.h"
#include "RIM_WidgetStageSelectActor.h"

//BeginPlay �� ���� ����
void URIM_WidgetStageSelect::NativeConstruct()
{
	//��ư Ŭ��
	btn_Stage01->OnPressed.AddDynamic(this, &URIM_WidgetStageSelect::Bind_btn_PlayStage01);
	btn_Stage02->OnPressed.AddDynamic(this, &URIM_WidgetStageSelect::Bind_btn_PlayStage02);
	btn_Stage03->OnPressed.AddDynamic(this, &URIM_WidgetStageSelect::Bind_btn_PlayStage03);
	btn_Stage04->OnPressed.AddDynamic(this, &URIM_WidgetStageSelect::Bind_btn_PlayStage04);
	btn_Stage05->OnPressed.AddDynamic(this, &URIM_WidgetStageSelect::Bind_btn_PlayStage05);
	btn_Back->OnPressed.AddDynamic(this, &URIM_WidgetStageSelect::Bind_btn_GoBack);

	
}


//Stage01 ��ư Ŭ���ϸ� WidgetStageSelectActor ���� �Լ� ����
void URIM_WidgetStageSelect::Bind_btn_PlayStage01()
{
	widgetStageSelectActor->PlayStage01();

}

//Stage02 ��ư Ŭ���ϸ� ����
UFUNCTION()
void URIM_WidgetStageSelect::Bind_btn_PlayStage02()
{
	widgetStageSelectActor->PlayStage02();

}

//Stage03 ��ư Ŭ���ϸ� ����
UFUNCTION()
void URIM_WidgetStageSelect::Bind_btn_PlayStage03()
{
	widgetStageSelectActor->PlayStage03();

}

//Stage04 ��ư Ŭ���ϸ� ����
UFUNCTION()
void URIM_WidgetStageSelect::Bind_btn_PlayStage04()
{
	widgetStageSelectActor->PlayStage04();

}

//Stage05 ��ư Ŭ���ϸ� ����
UFUNCTION()
void URIM_WidgetStageSelect::Bind_btn_PlayStage05()
{
	widgetStageSelectActor->PlayStage05();

}

//Back ��ư Ŭ���ϸ� ����
UFUNCTION()
void URIM_WidgetStageSelect::Bind_btn_GoBack()
{
	widgetStageSelectActor->GoBack();

}