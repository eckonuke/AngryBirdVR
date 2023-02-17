// Fill out your copyright notice in the Description page of Project Settings.


#include "RIM_WidgetStageSelectActor.h"
#include <UMG/Public/Components/WidgetComponent.h>
#include <Kismet/GameplayStatics.h>
#include "RIM_WidgetStageSelect.h"

// Sets default values
ARIM_WidgetStageSelectActor::ARIM_WidgetStageSelectActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//위젯 추가
	widgetStageSelect = CreateDefaultSubobject<UWidgetComponent>(TEXT("Stage Select Widget Component"));
	widgetStageSelect->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ARIM_WidgetStageSelectActor::BeginPlay()
{
	Super::BeginPlay();
	
	//WidgetStageSelectActor(이 곳) 의 함수를 WidgetStageSelect(위젯)이 실행 할 수 있게 해주는 코드
	if (widgetStageSelect != nullptr) //WidgetStageSelectActor 에 WidgetStageSelect 이 있으면
	{
		URIM_WidgetStageSelect* stageSelectWidget = Cast<URIM_WidgetStageSelect>(widgetStageSelect->GetWidget());

		if (stageSelectWidget != nullptr) //stageSelectWidget 이면
		{
			stageSelectWidget->widgetStageSelectActor = this;
		}
	}

}

// Called every frame
void ARIM_WidgetStageSelectActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


//WidgetStageSelect 에서 btn_Stage01 클릭 했을 때 실행 될 함수
void ARIM_WidgetStageSelectActor::PlayStage01()
{
	//스테이지1 으로 이동. Stage1_1 레벨 오픈
	UGameplayStatics::OpenLevel(GetWorld(), "Stage1_1");

}

//WidgetStageSelect 에서 btn_Stage02 클릭 했을 때 실행 될 함수
void ARIM_WidgetStageSelectActor::PlayStage02()
{
	//스테이지2 으로 이동. Stage1_2 레벨 오픈
	UGameplayStatics::OpenLevel(GetWorld(), "Stage1_2");

}

//WidgetStageSelect 에서 btn_Stage03 클릭 했을 때 실행 될 함수
void ARIM_WidgetStageSelectActor::PlayStage03()
{
	//스테이지3 으로 이동. Stage1_3 레벨 오픈
	UGameplayStatics::OpenLevel(GetWorld(), "Stage1_3");

}

//WidgetStageSelect 에서 btn_Stage04 클릭 했을 때 실행 될 함수
void ARIM_WidgetStageSelectActor::PlayStage04()
{
	//스테이지4 으로 이동. Stage1_4 레벨 오픈
	UGameplayStatics::OpenLevel(GetWorld(), "Stage1_4");

}

//WidgetStageSelect 에서 btn_Stage05 클릭 했을 때 실행 될 함수
void ARIM_WidgetStageSelectActor::PlayStage05()
{
	//스테이지5 으로 이동. Stage1_5 레벨 오픈
	UGameplayStatics::OpenLevel(GetWorld(), "Stage1_5");

}

//WidgetStageSelect 에서 btn_GoBack 클릭 했을 때 실행 될 함수
void ARIM_WidgetStageSelectActor::GoBack()
{
	//메인 화면으로 이동. 01_Main 레벨 오픈
	UGameplayStatics::OpenLevel(GetWorld(), "01_Main");

}