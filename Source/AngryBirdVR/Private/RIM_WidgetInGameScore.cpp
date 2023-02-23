// Fill out your copyright notice in the Description page of Project Settings.


#include "RIM_WidgetInGameScore.h"
#include <Kismet/GameplayStatics.h>
#include "Components/Button.h"
#include "RIM_WidgetInGameScoreActor.h"

//BeginPlay �� ���� ����
void URIM_WidgetInGameScore::NativeConstruct()
{
	//��ư Ŭ��
	btn_Menu->OnPressed.AddDynamic(this, &URIM_WidgetInGameScore::Bind_btn_GoMenu);
	btn_Restart->OnPressed.AddDynamic(this, &URIM_WidgetInGameScore::Bind_btn_GoRestart);
	btn_Next->OnPressed.AddDynamic(this, &URIM_WidgetInGameScore::Bind_btn_GoNext);
	
// 	Bind_Star1();
// 	Bind_Star2();
// 	Bind_Star3();

	Bind_Star_Yellow1();
	Bind_Star_Yellow2();
	Bind_Star_Yellow3();

}


//Menu ��ư Ŭ���ϸ� WidgetInGameScoreActor ���� �Լ� ����
void URIM_WidgetInGameScore::Bind_btn_GoMenu()
{
	widgetInGameScoreActor->GoMenu();

}

//�ٽý��� ��ư Ŭ���ϸ�
void URIM_WidgetInGameScore::Bind_btn_GoRestart()
{
	widgetInGameScoreActor->GoRestart();

}

//���� �������� ��ư Ŭ���ϸ�
void URIM_WidgetInGameScore::Bind_btn_GoNext()
{
	widgetInGameScoreActor->GoNext();
}


//[��]
// void URIM_WidgetInGameScore::Bind_Star1()
// {
// 	
// }
// 
// void URIM_WidgetInGameScore::Bind_Star2()
// {
// 
// }
// 
// void URIM_WidgetInGameScore::Bind_Star3()
// {
// 
// }

void URIM_WidgetInGameScore::Bind_Star_Yellow1()
{
	widgetInGameScoreActor->yellowStar1();
}

void URIM_WidgetInGameScore::Bind_Star_Yellow2()
{
	widgetInGameScoreActor->yellowStar2();
}

void URIM_WidgetInGameScore::Bind_Star_Yellow3()
{
	widgetInGameScoreActor->yellowStar3();
}