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

	//���� �߰�
	widgetStageSelect = CreateDefaultSubobject<UWidgetComponent>(TEXT("Stage Select Widget Component"));
	widgetStageSelect->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ARIM_WidgetStageSelectActor::BeginPlay()
{
	Super::BeginPlay();
	
	//WidgetStageSelectActor(�� ��) �� �Լ��� WidgetStageSelect(����)�� ���� �� �� �ְ� ���ִ� �ڵ�
	if (widgetStageSelect != nullptr) //WidgetStageSelectActor �� WidgetStageSelect �� ������
	{
		URIM_WidgetStageSelect* stageSelectWidget = Cast<URIM_WidgetStageSelect>(widgetStageSelect->GetWidget());

		if (stageSelectWidget != nullptr) //stageSelectWidget �̸�
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


//WidgetStageSelect ���� btn_Stage01 Ŭ�� ���� �� ���� �� �Լ�
void ARIM_WidgetStageSelectActor::PlayStage01()
{
	//��������1 ���� �̵�. Stage1_1 ���� ����
	UGameplayStatics::OpenLevel(GetWorld(), "Stage1_1");

}

//WidgetStageSelect ���� btn_Stage02 Ŭ�� ���� �� ���� �� �Լ�
void ARIM_WidgetStageSelectActor::PlayStage02()
{
	//��������2 ���� �̵�. Stage1_2 ���� ����
	UGameplayStatics::OpenLevel(GetWorld(), "Stage1_2");

}

//WidgetStageSelect ���� btn_Stage03 Ŭ�� ���� �� ���� �� �Լ�
void ARIM_WidgetStageSelectActor::PlayStage03()
{
	//��������3 ���� �̵�. Stage1_3 ���� ����
	UGameplayStatics::OpenLevel(GetWorld(), "Stage1_3");

}

//WidgetStageSelect ���� btn_Stage04 Ŭ�� ���� �� ���� �� �Լ�
void ARIM_WidgetStageSelectActor::PlayStage04()
{
	//��������4 ���� �̵�. Stage1_4 ���� ����
	UGameplayStatics::OpenLevel(GetWorld(), "Stage1_4");

}

//WidgetStageSelect ���� btn_Stage05 Ŭ�� ���� �� ���� �� �Լ�
void ARIM_WidgetStageSelectActor::PlayStage05()
{
	//��������5 ���� �̵�. Stage1_5 ���� ����
	UGameplayStatics::OpenLevel(GetWorld(), "Stage1_5");

}

//WidgetStageSelect ���� btn_GoBack Ŭ�� ���� �� ���� �� �Լ�
void ARIM_WidgetStageSelectActor::GoBack()
{
	//���� ȭ������ �̵�. 01_Main ���� ����
	UGameplayStatics::OpenLevel(GetWorld(), "01_Main");

}