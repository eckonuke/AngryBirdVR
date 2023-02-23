// Fill out your copyright notice in the Description page of Project Settings.


#include "AngryBirdVR_GameModeBase.h"
#include <Kismet/GameplayStatics.h>
#include "RIM_WidgetInGameScoreActor.h"
#include "RIM_Player.h"
#include "RIM_Pig.h"
#include "RIM_WidgetInGameFailActor.h"

AAngryBirdVR_GameModeBase::AAngryBirdVR_GameModeBase() //�߰�
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


}

void AAngryBirdVR_GameModeBase::BeginPlay() //�߰�
{
	Super::BeginPlay();
	

}

void AAngryBirdVR_GameModeBase::Tick(float DeltaTime) //�߰�
{
	Super::Tick(DeltaTime);

	currentTime += DeltaTime;
	if (player) {
		if (EnemyAllDie == true) //���� �� ������
		{
			if (currentTime < 2) //2�� ������
			{
				//���� ������ �����ش� ���� �¸� ȭ�� (������ �� �߰�)
				GetWorld()->SpawnActor<ARIM_WidgetInGameScoreActor>(ARIM_WidgetInGameScoreActor::StaticClass(), player->GetActorLocation() + player->GetActorForwardVector() * 200, FRotator(0.0f, 180.0f, 0.0f)); //�ڡڡڡڡڡ�
			}
		}
		//���� 0�� �̰� ���� ����ִٸ�
		else if (player->birdCount == 0) {
			if (currentTime < 2) //2�� ������
			{
				//������ ȭ���� �����ش�
				GetWorld()->SpawnActor<ARIM_WidgetInGameFailActor>(ARIM_WidgetInGameFailActor::StaticClass(), player->GetActorLocation() + player->GetActorForwardVector() * 200, FRotator(0.0f, 180.0f, 0.0f));
			}
			
		}
	}
	FindEnemyActor();
}


//��(����)�� �� �׾����� üũ
void AAngryBirdVR_GameModeBase::FindEnemyActor()
{
	//TArray<AActor*> tarrayPig; //�ƿ����̳ʿ� �ִ� '��� ����'�� �迭...?
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ARIM_Pig::StaticClass(), pig); //ã���� �ϴ� Ŭ����(Pig)�� ����� ���͸� ��� �� ã�´�
	if (pig.Num() == 0) //������ 0 �̸�
	{
		EnemyAllDie = true;
	}
	else {
		EnemyAllDie = false;
	}
	

}
