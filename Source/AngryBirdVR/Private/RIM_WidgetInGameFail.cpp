// Fill out your copyright notice in the Description page of Project Settings.


#include "RIM_WidgetInGameFail.h"
#include <Kismet/GameplayStatics.h>
#include "Components/Button.h"
#include "RIM_WidgetInGameFailActor.h"

//BeginPlay 와 같은 동작
void URIM_WidgetInGameFail::NativeConstruct()
{
	//버튼 클릭
	btn_Menu->OnPressed.AddDynamic(this, &URIM_WidgetInGameFail::Bind_btn_GoMenu);
	btn_Restart->OnPressed.AddDynamic(this, &URIM_WidgetInGameFail::Bind_btn_GoRestart);

}


//Menu 버튼 클릭하면 WidgetInGameFailActor 에서 함수 실행
void URIM_WidgetInGameFail::Bind_btn_GoMenu()
{
	widgetInGameFailActor->GoMenu();

}

//다시시작 버튼 클릭하면
void URIM_WidgetInGameFail::Bind_btn_GoRestart()
{
	widgetInGameFailActor->GoRestart();

}