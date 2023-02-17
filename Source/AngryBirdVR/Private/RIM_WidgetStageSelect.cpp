// Fill out your copyright notice in the Description page of Project Settings.


#include "RIM_WidgetStageSelect.h"
#include <Kismet/GameplayStatics.h>
#include "Components/Button.h"
#include "RIM_WidgetStageSelectActor.h"

//BeginPlay 와 같은 동작
void URIM_WidgetStageSelect::NativeConstruct()
{
	//버튼 클릭
	btn_Stage01->OnPressed.AddDynamic(this, &URIM_WidgetStageSelect::Bind_btn_PlayStage01);
	btn_Stage02->OnPressed.AddDynamic(this, &URIM_WidgetStageSelect::Bind_btn_PlayStage02);
	btn_Stage03->OnPressed.AddDynamic(this, &URIM_WidgetStageSelect::Bind_btn_PlayStage03);
	btn_Stage04->OnPressed.AddDynamic(this, &URIM_WidgetStageSelect::Bind_btn_PlayStage04);
	btn_Stage05->OnPressed.AddDynamic(this, &URIM_WidgetStageSelect::Bind_btn_PlayStage05);
	btn_Back->OnPressed.AddDynamic(this, &URIM_WidgetStageSelect::Bind_btn_GoBack);

	
}


//Stage01 버튼 클릭하면 WidgetStageSelectActor 에서 함수 실행
void URIM_WidgetStageSelect::Bind_btn_PlayStage01()
{
	widgetStageSelectActor->PlayStage01();

}

//Stage02 버튼 클릭하면 실행
UFUNCTION()
void URIM_WidgetStageSelect::Bind_btn_PlayStage02()
{
	widgetStageSelectActor->PlayStage02();

}

//Stage03 버튼 클릭하면 실행
UFUNCTION()
void URIM_WidgetStageSelect::Bind_btn_PlayStage03()
{
	widgetStageSelectActor->PlayStage03();

}

//Stage04 버튼 클릭하면 실행
UFUNCTION()
void URIM_WidgetStageSelect::Bind_btn_PlayStage04()
{
	widgetStageSelectActor->PlayStage04();

}

//Stage05 버튼 클릭하면 실행
UFUNCTION()
void URIM_WidgetStageSelect::Bind_btn_PlayStage05()
{
	widgetStageSelectActor->PlayStage05();

}

//Back 버튼 클릭하면 실행
UFUNCTION()
void URIM_WidgetStageSelect::Bind_btn_GoBack()
{
	widgetStageSelectActor->GoBack();

}