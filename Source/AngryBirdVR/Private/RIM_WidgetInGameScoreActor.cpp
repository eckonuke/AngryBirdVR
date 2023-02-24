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

	//���� �߰�
	widgetInGameScore = CreateDefaultSubobject<UWidgetComponent>(TEXT("In Game Score Widget Component"));
	widgetInGameScore->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ARIM_WidgetInGameScoreActor::BeginPlay()
{
	Super::BeginPlay();
	
	//WidgetInGameScoreActor(�� ��) �� �Լ��� WidgetInGameScore(����)�� ���� �� �� �ְ� ���ִ� �ڵ�
	if (widgetInGameScore != nullptr) //WidgetInGameScoreActor �� WidgetInGameScore �� ������
	{
		URIM_WidgetInGameScore* inGameScoreWidget = Cast<URIM_WidgetInGameScore>(widgetInGameScore->GetWidget());

		if (inGameScoreWidget != nullptr) //inGameScoreWidget �̸�
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


//WidgetInGameScore ���� btn_Menu Ŭ�� ���� �� ���� �� �Լ�
void ARIM_WidgetInGameScoreActor::GoMenu()
{
	//���� ȭ������ �̵�. 01_Main ���� ����
	UGameplayStatics::OpenLevel(GetWorld(), "01_Main");

}

//WidgetInGameScore ���� btn_Restart Ŭ�� ���� �� ���� �� �Լ�
void ARIM_WidgetInGameScoreActor::GoRestart()
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

//WidgetInGameScore ���� btn_Next Ŭ�� ���� �� ���� �� �Լ�
void ARIM_WidgetInGameScoreActor::GoNext()
{
	//���� �������� ���� ����

	FString levelName = UGameplayStatics::GetCurrentLevelName(GetWorld());
	
	if (levelName.Contains("Stage1_1"))  //���� ��������1 �̸�
	{
		//��������2 ���� �̵�. Stage1_2 ���� ����
		UGameplayStatics::OpenLevel(GetWorld(), "Stage1_2"); 
	}
	else if (levelName.Contains("Stage1_2")) //���� ��������2 �̸�
	{
		//��������3 ���� �̵�. Stage1_3 ���� ����
		UGameplayStatics::OpenLevel(GetWorld(), "Stage1_3");
	}
	else if (levelName.Contains("Stage1_3")) //���� ��������3 �̸�
	{
		UGameplayStatics::OpenLevel(GetWorld(), "01_Main");
	}
}

//��
void ARIM_WidgetInGameScoreActor::yellowStar1()
{
	//���� ���ǿ� ���� ��1�� ����...?


}

void ARIM_WidgetInGameScoreActor::yellowStar2()
{
	//���� ���ǿ� ���� ��2�� ����...?


}

void ARIM_WidgetInGameScoreActor::yellowStar3()
{
	//���� ���ǿ� ���� ��3�� ����...?


}