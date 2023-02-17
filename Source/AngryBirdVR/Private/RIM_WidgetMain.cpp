// Fill out your copyright notice in the Description page of Project Settings.


#include "RIM_WidgetMain.h"
#include <Kismet/GameplayStatics.h>
#include "Components/Button.h"
#include "RIM_WidgetMainActor.h"

//BeginPlay �� ���� ����
void URIM_WidgetMain::NativeConstruct()
{
	//��ư Ŭ��
	btn_PlayStart->OnPressed.AddDynamic(this, &URIM_WidgetMain::Bind_btn_PlayGame);


}


//play ��ư Ŭ���ϸ� WidgetMainActor �� PlayGameStart �Լ� ����
void URIM_WidgetMain::Bind_btn_PlayGame()
{
	UE_LOG(LogTemp, Warning, TEXT("Bind_btn_PlayGame !!!!!!!!!!!!!!!!!!!!"));

	widgetMainActor->PlayGame();

}

