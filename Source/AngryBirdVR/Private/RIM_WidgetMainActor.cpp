// Fill out your copyright notice in the Description page of Project Settings.


#include "RIM_WidgetMainActor.h"
#include <UMG/Public/Components/WidgetComponent.h>
#include "RIM_WidgetMain.h"
#include <Kismet/GameplayStatics.h>

// Sets default values
ARIM_WidgetMainActor::ARIM_WidgetMainActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//위젯 추가
	widgetMain = CreateDefaultSubobject<UWidgetComponent>(TEXT("Main Widget Component"));
	widgetMain->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ARIM_WidgetMainActor::BeginPlay()
{
	Super::BeginPlay();
	
	//WidgetMainActor(이 곳) 의 함수를 WidgetMain(위젯)이 실행 할 수 있게 해주는 코드
	if (widgetMain != nullptr) //WidgetMainActor 에 widgetMain 이 있으면
	{
		URIM_WidgetMain* mainWidget = Cast<URIM_WidgetMain>(widgetMain->GetWidget());

		if (mainWidget != nullptr) //mainWidget 이면
		{
			mainWidget->widgetMainActor = this;
		}
	}

}

// Called every frame
void ARIM_WidgetMainActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


//WidgetMain 에서 btn_PlayGameStart 클릭 했을 때 실행 될 함수
void ARIM_WidgetMainActor::PlayGame()
{
	UE_LOG(LogTemp, Warning, TEXT("01_Main ---> Click ---> Open ---> 02_StageSelect"));

	//02_StageSelect 레벨 오픈
	UGameplayStatics::OpenLevel(GetWorld(), "02_StageSelect");

}