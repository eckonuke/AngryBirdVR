// Fill out your copyright notice in the Description page of Project Settings.


#include "RIM_WidgetInGameFail.h"
#include <Kismet/GameplayStatics.h>
#include "Components/Button.h"
#include "RIM_WidgetInGameFailActor.h"

//BeginPlay �� ���� ����
void URIM_WidgetInGameFail::NativeConstruct()
{
	//��ư Ŭ��
	btn_Menu->OnPressed.AddDynamic(this, &URIM_WidgetInGameFail::Bind_btn_GoMenu);
	btn_Restart->OnPressed.AddDynamic(this, &URIM_WidgetInGameFail::Bind_btn_GoRestart);

}


//Menu ��ư Ŭ���ϸ� WidgetInGameFailActor ���� �Լ� ����
void URIM_WidgetInGameFail::Bind_btn_GoMenu()
{
	widgetInGameFailActor->GoMenu();

}

//�ٽý��� ��ư Ŭ���ϸ�
void URIM_WidgetInGameFail::Bind_btn_GoRestart()
{
	widgetInGameFailActor->GoRestart();

}