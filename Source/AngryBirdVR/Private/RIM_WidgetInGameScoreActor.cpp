// Fill out your copyright notice in the Description page of Project Settings.


#include "RIM_WidgetInGameScoreActor.h"
#include <UMG/Public/Components/WidgetComponent.h>
#include <Kismet/GameplayStatics.h>
#include "RIM_WidgetInGameScore.h"

// Sets default values
ARIM_WidgetInGameScoreActor::ARIM_WidgetInGameScoreActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//위젯 추가
	widgetInGameScore = CreateDefaultSubobject<UWidgetComponent>(TEXT("In Game Score Widget Component"));
	widgetInGameScore->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ARIM_WidgetInGameScoreActor::BeginPlay()
{
	Super::BeginPlay();
	
	//WidgetInGameScoreActor(이 곳) 의 함수를 WidgetInGameScore(위젯)이 실행 할 수 있게 해주는 코드
	if (widgetInGameScore != nullptr) //WidgetInGameScoreActor 에 WidgetInGameScore 이 있으면
	{
		URIM_WidgetInGameScore* inGameScoreWidget = Cast<URIM_WidgetInGameScore>(widgetInGameScore->GetWidget());

		if (inGameScoreWidget != nullptr) //inGameScoreWidget 이면
		{
			inGameScoreWidget->widgetInGameScoreActor = this;
		}
	}

}

// Called every frame
void ARIM_WidgetInGameScoreActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


//WidgetInGameScore 에서 btn_Menu 클릭 했을 때 실행 될 함수
void ARIM_WidgetInGameScoreActor::GoMenu()
{
	//메인 화면으로 이동. 01_Main 레벨 오픈
	UGameplayStatics::OpenLevel(GetWorld(), "01_Main");

}

//WidgetInGameScore 에서 btn_Restart 클릭 했을 때 실행 될 함수
void ARIM_WidgetInGameScoreActor::GoRestart()
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

//WidgetInGameScore 에서 btn_Next 클릭 했을 때 실행 될 함수
void ARIM_WidgetInGameScoreActor::GoNext()
{
	//다음 스테이지 레벨 오픈

	FString levelName = UGameplayStatics::GetCurrentLevelName(GetWorld());
	
	if (levelName.Contains("Stage1_1"))  //현재 스테이지1 이면
	{
		//스테이지2 으로 이동. Stage1_2 레벨 오픈
		UGameplayStatics::OpenLevel(GetWorld(), "Stage1_2"); 
	}
	else if (levelName.Contains("Stage1_2")) //현재 스테이지2 이면
	{
		//스테이지3 으로 이동. Stage1_3 레벨 오픈
		UGameplayStatics::OpenLevel(GetWorld(), "Stage1_3");
	}
	else if (levelName.Contains("Stage1_3")) //현재 스테이지3 이면
	{
		UGameplayStatics::OpenLevel(GetWorld(), "01_Main");
	}
}

//별
void ARIM_WidgetInGameScoreActor::yellowStar1()
{
	//점수 조건에 따라 별1개 노출...?


}

void ARIM_WidgetInGameScoreActor::yellowStar2()
{
	//점수 조건에 따라 별2개 노출...?


}

void ARIM_WidgetInGameScoreActor::yellowStar3()
{
	//점수 조건에 따라 별3개 노출...?


}