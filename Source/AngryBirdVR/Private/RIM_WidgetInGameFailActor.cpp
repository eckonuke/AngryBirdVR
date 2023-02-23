// Fill out your copyright notice in the Description page of Project Settings.


#include "RIM_WidgetInGameFailActor.h"
#include <UMG/Public/Components/WidgetComponent.h>
#include <Kismet/GameplayStatics.h>
#include "RIM_WidgetInGameFail.h"

// Sets default values
ARIM_WidgetInGameFailActor::ARIM_WidgetInGameFailActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//위젯 추가
	widgetInGameFail = CreateDefaultSubobject<UWidgetComponent>(TEXT("In Game Fail Widget Component"));
	widgetInGameFail->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ARIM_WidgetInGameFailActor::BeginPlay()
{
	Super::BeginPlay();
	
	//WidgetInGameFailActor(이 곳) 의 함수를 WidgetInGameFail(위젯)이 실행 할 수 있게 해주는 코드
	if (widgetInGameFail != nullptr) //WidgetInGameFailActor 에 WidgetInGameFail 이 있으면
	{
		URIM_WidgetInGameFail* inGameFailWidget = Cast<URIM_WidgetInGameFail>(widgetInGameFail->GetWidget());

		if (inGameFailWidget != nullptr) //inGameFailWidget 이면
		{
			inGameFailWidget->widgetInGameFailActor = this;
		}
	}

}

// Called every frame
void ARIM_WidgetInGameFailActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


//WidgetInGameFail 에서 btn_Menu 클릭 했을 때 실행 될 함수
void ARIM_WidgetInGameFailActor::GoMenu()
{
	//메인 화면으로 이동. 01_Main 레벨 오픈
	UGameplayStatics::OpenLevel(GetWorld(), "01_Main");

}

//WidgetInGameFail 에서 btn_Restart 클릭 했을 때 실행 될 함수
void ARIM_WidgetInGameFailActor::GoRestart()
{
	//해당 스테이지 게임 처음부터 시작 = 해당 레벨 오픈

	FString levelName = UGameplayStatics::GetCurrentLevelName(GetWorld());

	//현재 스테이지1 이면
	if (levelName.Contains("Stage1_1"))
	{
		//스테이지1 을 연다
		UGameplayStatics::OpenLevel(GetWorld(), "Stage1_1");
	}
	//현재 스테이지2 이면
	else if (levelName.Contains("Stage1_2"))
	{
		//스테이지2 을 연다
		UGameplayStatics::OpenLevel(GetWorld(), "Stage1_2");
	}
	//현재 스테이지3 이면
	else if (levelName.Contains("Stage1_3"))
	{
		//스테이지3 을 연다
		UGameplayStatics::OpenLevel(GetWorld(), "Stage1_3");
	}


}