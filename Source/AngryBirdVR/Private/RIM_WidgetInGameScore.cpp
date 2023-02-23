// Fill out your copyright notice in the Description page of Project Settings.


#include "RIM_WidgetInGameScore.h"
#include <Kismet/GameplayStatics.h>
#include "Components/Button.h"
#include "RIM_WidgetInGameScoreActor.h"
#include <UMG/Public/Components/Image.h>
#include "RIM_Player.h"
#include <UMG/Public/Components/TextBlock.h>
#include "RIM_Pig.h"

//BeginPlay �� ���� ����
void URIM_WidgetInGameScore::NativeConstruct()
{
	//��ư Ŭ��
	btn_Menu->OnPressed.AddDynamic(this, &URIM_WidgetInGameScore::Bind_btn_GoMenu);
	btn_Restart->OnPressed.AddDynamic(this, &URIM_WidgetInGameScore::Bind_btn_GoRestart);
	btn_Next->OnPressed.AddDynamic(this, &URIM_WidgetInGameScore::Bind_btn_GoNext);
	Init();
	
	starCalc(player->score);
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

void URIM_WidgetInGameScore::starCalc(int32 point)
{
	int32 starCount = player->birdCount;
	if (starCount >= 2) {
		img_Star_Yellow1->SetVisibility(ESlateVisibility::Visible);
		img_Star_Yellow2->SetVisibility(ESlateVisibility::Visible);
		img_Star_Yellow3->SetVisibility(ESlateVisibility::Visible);
	}
	else if (starCount >= 1) {
		img_Star_Yellow1->SetVisibility(ESlateVisibility::Visible);
		img_Star_Yellow2->SetVisibility(ESlateVisibility::Visible);
	}
	else if (starCount == 0) {
		img_Star_Yellow1->SetVisibility(ESlateVisibility::Visible);
	}
	FString str = FString::FromInt(player->score);
	Score->SetText(FText::FromString(str));
}

void URIM_WidgetInGameScore::Init() {
	player = Cast<ARIM_Player>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	img_Star_Yellow1->SetVisibility(ESlateVisibility::Hidden);
	img_Star_Yellow2->SetVisibility(ESlateVisibility::Hidden);
	img_Star_Yellow3->SetVisibility(ESlateVisibility::Hidden);
}
