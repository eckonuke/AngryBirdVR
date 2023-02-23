// Fill out your copyright notice in the Description page of Project Settings.


#include "AngryBirdVR_GameModeBase.h"
#include <Kismet/GameplayStatics.h>
#include "RIM_WidgetInGameScoreActor.h"
#include "RIM_Player.h"
#include "RIM_Pig.h"
#include "RIM_WidgetInGameFailActor.h"

AAngryBirdVR_GameModeBase::AAngryBirdVR_GameModeBase() //추가
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


}

void AAngryBirdVR_GameModeBase::BeginPlay() //추가
{
	Super::BeginPlay();
	player = Cast<ARIM_Player>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
}

void AAngryBirdVR_GameModeBase::Tick(float DeltaTime) //추가
{
	Super::Tick(DeltaTime);
	//if (player) {
	//	if (spawnedScreen == false) {
	//		spawnedScreen = true;
	//		if (player->finish == true) //적이 다 죽으면
	//		{
	//			//점수 위젯을 보여준다 게임 승리 화면 (점수와 별 추가)
	//			//★★★★★★
	//			ARIM_WidgetInGameScoreActor* screen = GetWorld()->SpawnActor<ARIM_WidgetInGameScoreActor>
	//				(ARIM_WidgetInGameScoreActor::StaticClass(), player->GetActorLocation() + player->GetActorForwardVector() * 200, FRotator(0.0f, 180.0f, 0.0f));

	//		}
	//		//새가 0개 이고 적이 살아있다면
	//		else if (player->birdCount == 0) {
	//			//실패한 화면을 보여준다
	//			ARIM_WidgetInGameFailActor* screen = GetWorld()->SpawnActor<ARIM_WidgetInGameFailActor>
	//				(ARIM_WidgetInGameFailActor::StaticClass(), player->GetActorLocation() + player->GetActorForwardVector() * 200, FRotator(0.0f, 180.0f, 0.0f));
	//		}
	//	}
	//}
}