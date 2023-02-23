// Fill out your copyright notice in the Description page of Project Settings.


#include "RIM_WidgetInGameScore.h"
#include <Kismet/GameplayStatics.h>
#include "Components/Button.h"
#include "RIM_WidgetInGameScoreActor.h"
#include <UMG/Public/Components/Image.h>
#include "RIM_Player.h"
#include <UMG/Public/Components/TextBlock.h>
#include "RIM_Pig.h"

//BeginPlay 와 같은 동작
void URIM_WidgetInGameScore::NativeConstruct()
{
	//버튼 클릭
	btn_Menu->OnPressed.AddDynamic(this, &URIM_WidgetInGameScore::Bind_btn_GoMenu);
	btn_Restart->OnPressed.AddDynamic(this, &URIM_WidgetInGameScore::Bind_btn_GoRestart);
	btn_Next->OnPressed.AddDynamic(this, &URIM_WidgetInGameScore::Bind_btn_GoNext);
	Init();
	
	starCalc(player->score);
}


//Menu 버튼 클릭하면 WidgetInGameScoreActor 에서 함수 실행
void URIM_WidgetInGameScore::Bind_btn_GoMenu()
{
	widgetInGameScoreActor->GoMenu();

}

//다시시작 버튼 클릭하면
void URIM_WidgetInGameScore::Bind_btn_GoRestart()
{
	widgetInGameScoreActor->GoRestart();

}

//다음 스테이지 버튼 클릭하면
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
