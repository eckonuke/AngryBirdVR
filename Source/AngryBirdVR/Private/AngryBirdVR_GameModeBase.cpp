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
	

}

void AAngryBirdVR_GameModeBase::Tick(float DeltaTime) //추가
{
	Super::Tick(DeltaTime);

	currentTime += DeltaTime;
	if (player) {
		if (EnemyAllDie == true) //적이 다 죽으면
		{
			if (currentTime < 2) //2초 지나고
			{
				//점수 위젯을 보여준다 게임 승리 화면 (점수와 별 추가)
				GetWorld()->SpawnActor<ARIM_WidgetInGameScoreActor>(ARIM_WidgetInGameScoreActor::StaticClass(), player->GetActorLocation() + player->GetActorForwardVector() * 200, FRotator(0.0f, 180.0f, 0.0f)); //★★★★★★
			}
		}
		//새가 0개 이고 적이 살아있다면
		else if (player->birdCount == 0) {
			if (currentTime < 2) //2초 지나고
			{
				//실패한 화면을 보여준다
				GetWorld()->SpawnActor<ARIM_WidgetInGameFailActor>(ARIM_WidgetInGameFailActor::StaticClass(), player->GetActorLocation() + player->GetActorForwardVector() * 200, FRotator(0.0f, 180.0f, 0.0f));
			}
			
		}
	}
	FindEnemyActor();
}


//적(돼지)이 다 죽었는지 체크
void AAngryBirdVR_GameModeBase::FindEnemyActor()
{
	//TArray<AActor*> tarrayPig; //아웃라이너에 있는 '모든 액터'의 배열...?
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ARIM_Pig::StaticClass(), pig); //찾고자 하는 클래스(Pig)를 상속한 액터를 모두 다 찾는다
	if (pig.Num() == 0) //돼지가 0 이면
	{
		EnemyAllDie = true;
	}
	else {
		EnemyAllDie = false;
	}
	

}
