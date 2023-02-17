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

	//���� �߰�
	widgetMain = CreateDefaultSubobject<UWidgetComponent>(TEXT("Main Widget Component"));
	widgetMain->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ARIM_WidgetMainActor::BeginPlay()
{
	Super::BeginPlay();
	
	//WidgetMainActor(�� ��) �� �Լ��� WidgetMain(����)�� ���� �� �� �ְ� ���ִ� �ڵ�
	if (widgetMain != nullptr) //WidgetMainActor �� widgetMain �� ������
	{
		URIM_WidgetMain* mainWidget = Cast<URIM_WidgetMain>(widgetMain->GetWidget());

		if (mainWidget != nullptr) //mainWidget �̸�
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


//WidgetMain ���� btn_PlayGameStart Ŭ�� ���� �� ���� �� �Լ�
void ARIM_WidgetMainActor::PlayGame()
{
	UE_LOG(LogTemp, Warning, TEXT("01_Main ---> Click ---> Open ---> 02_StageSelect"));

	//02_StageSelect ���� ����
	UGameplayStatics::OpenLevel(GetWorld(), "02_StageSelect");

}