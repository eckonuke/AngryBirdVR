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
	player = Cast<ARIM_Player>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
}

void AAngryBirdVR_GameModeBase::Tick(float DeltaTime) //�߰�
{
	Super::Tick(DeltaTime);
	//if (player) {
	//	if (spawnedScreen == false) {
	//		spawnedScreen = true;
	//		if (player->finish == true) //���� �� ������
	//		{
	//			//���� ������ �����ش� ���� �¸� ȭ�� (������ �� �߰�)
	//			//�ڡڡڡڡڡ�
	//			ARIM_WidgetInGameScoreActor* screen = GetWorld()->SpawnActor<ARIM_WidgetInGameScoreActor>
	//				(ARIM_WidgetInGameScoreActor::StaticClass(), player->GetActorLocation() + player->GetActorForwardVector() * 200, FRotator(0.0f, 180.0f, 0.0f));

	//		}
	//		//���� 0�� �̰� ���� ����ִٸ�
	//		else if (player->birdCount == 0) {
	//			//������ ȭ���� �����ش�
	//			ARIM_WidgetInGameFailActor* screen = GetWorld()->SpawnActor<ARIM_WidgetInGameFailActor>
	//				(ARIM_WidgetInGameFailActor::StaticClass(), player->GetActorLocation() + player->GetActorForwardVector() * 200, FRotator(0.0f, 180.0f, 0.0f));
	//		}
	//	}
	//}
}