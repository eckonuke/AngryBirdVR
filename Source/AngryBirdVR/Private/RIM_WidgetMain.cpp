// Fill out your copyright notice in the Description page of Project Settings.


#include "RIM_WidgetMain.h"
#include <Kismet/GameplayStatics.h>
#include "Components/Button.h"
#include "RIM_WidgetMainActor.h"

//BeginPlay 와 같은 동작
void URIM_WidgetMain::NativeConstruct()
{
	//버튼 클릭
	btn_PlayStart->OnPressed.AddDynamic(this, &URIM_WidgetMain::Bind_btn_PlayGame);


}


//play 버튼 클릭하면 WidgetMainActor 의 PlayGameStart 함수 실행
void URIM_WidgetMain::Bind_btn_PlayGame()
{
	UE_LOG(LogTemp, Warning, TEXT("Bind_btn_PlayGame !!!!!!!!!!!!!!!!!!!!"));

	widgetMainActor->PlayGame();

}

