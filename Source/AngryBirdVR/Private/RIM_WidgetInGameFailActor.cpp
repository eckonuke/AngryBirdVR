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

	//���� �߰�
	widgetInGameFail = CreateDefaultSubobject<UWidgetComponent>(TEXT("In Game Fail Widget Component"));
	widgetInGameFail->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ARIM_WidgetInGameFailActor::BeginPlay()
{
	Super::BeginPlay();
	
	//WidgetInGameFailActor(�� ��) �� �Լ��� WidgetInGameFail(����)�� ���� �� �� �ְ� ���ִ� �ڵ�
	if (widgetInGameFail != nullptr) //WidgetInGameFailActor �� WidgetInGameFail �� ������
	{
		URIM_WidgetInGameFail* inGameFailWidget = Cast<URIM_WidgetInGameFail>(widgetInGameFail->GetWidget());

		if (inGameFailWidget != nullptr) //inGameFailWidget �̸�
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


//WidgetInGameFail ���� btn_Menu Ŭ�� ���� �� ���� �� �Լ�
void ARIM_WidgetInGameFailActor::GoMenu()
{
	//���� ȭ������ �̵�. 01_Main ���� ����
	UGameplayStatics::OpenLevel(GetWorld(), "01_Main");

}

//WidgetInGameFail ���� btn_Restart Ŭ�� ���� �� ���� �� �Լ�
void ARIM_WidgetInGameFailActor::GoRestart()
{
	//�ش� �������� ���� ó������ ���� = �ش� ���� ����

	FString levelName = UGameplayStatics::GetCurrentLevelName(GetWorld());

	//���� ��������1 �̸�
	if (levelName.Contains("Stage1_1"))
	{
		//��������1 �� ����
		UGameplayStatics::OpenLevel(GetWorld(), "Stage1_1");
	}
	//���� ��������2 �̸�
	else if (levelName.Contains("Stage1_2"))
	{
		//��������2 �� ����
		UGameplayStatics::OpenLevel(GetWorld(), "Stage1_2");
	}
	//���� ��������3 �̸�
	else if (levelName.Contains("Stage1_3"))
	{
		//��������3 �� ����
		UGameplayStatics::OpenLevel(GetWorld(), "Stage1_3");
	}


}