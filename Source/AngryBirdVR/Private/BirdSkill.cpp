// Fill out your copyright notice in the Description page of Project Settings.


#include "BirdSkill.h"
#include "RIM_Player.h"
#include "EnhancedInputComponent.h"
#include <Components/TextRenderComponent.h>
#include "RIM_BirdBlue.h"
#include <Engine/World.h>


// Sets default values for this component's properties
UBirdSkill::UBirdSkill()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	//파란새 클레스를 가져온다
// 	ConstructorHelpers::FClassFinder<ARIM_BirdBlue> tempBlue(TEXT("/Script/Engine.Blueprint'/Game/BluePrints/BP_BirdBlue.BP_BirdBlue_C'")); // 블루프린트 경로. _C'
// 	if (tempBlue.Succeeded())
// 	{
// 		blueFactory = tempBlue.Class; //BP_BirdBlue 세팅 됨
// 	}


}


// Called when the game starts
void UBirdSkill::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UBirdSkill::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


//[SetupPlayerInputComponent] 가상합수
void UBirdSkill::SetupPlayerInputComponent(class UEnhancedInputComponent* PlayerInputComponent)
{
	//Super::SetupPlayerInputComponent(PlayerInputComponent); //★★★다른 파일에서 가상함수 만들 때 Super 사용했는데 여긴 필요 없는거야? 왜?

	//오른손 그립 ---> 새 스킬 사용 ★★★실제 게임에서는 오른손 트리거 사용
	//PlayerInputComponent->BindAction(rightGrip, ETriggerEvent::Started, this, &UBirdSkill::inputSkill);
	



}


// void UBirdSkill::inputSkill()
// {
// 	FString msg = FString(__FUNCTION__); //확인용 로그
// 	player->logRight->SetText(FText::FromString(msg)); //확인용 로그
// 
// 
// 	//만약 새총에 파란새가 보이는 상태면...? 만약 새총에 파란새가 스폰되면...?
// 	//if (player->meshLeftHand->IsVisible() == true)
// 		
// 	FRotator actorRot;
// 	actorRot = birdBlue->GetActorRotation();
// 	actorRot.Yaw -= 30;
// 
// 	//기존 파란새 위치에서 파란새 1마리를 스폰한다. 기존 파란새에서 왼쪽방향(회전Yaw-30)으로 스폰
// 	// 발사된다. 날아간다
// 	//GetWorld()->SpawnActor<ARIM_BirdBlue>(blueFactory, birdBlue->GetActorLocation() + birdBlue->GetActorForwardVector() * 200, actorRot.Yaw);
// 	//GetWorld()->SpawnActor<ARIM_BirdBlue>(blueFactory, birdBlue->GetActorLocation() + birdBlue->GetActorForwardVector() * 200, birdBlue->GetActorRotation());
// 	  
// 	//기존 파란새 위치에서 파란새 1마리를 스폰한다. /기존 파란새에서 오른쪽방향(회전Yaw+30)으로 스폰
// 	// 발사된다. 날아간다
// 
// }








//blueBirdPos Transform 을 가져온다
//player->meshLeftHand->GetSocketTransform(TEXT("BlueSkillPos")); //가져오고자 하는 소켓 이름 넣는다
//FTransform blueFire = player->meshLeftHand->GetSocketTransform(TEXT("BlueSkillPos"));

//파란새 생성(위치, 회전 세팅)
//월드에서 파란새 가져온다
//GetWorld()->SpawnActor<ARIM_BirdBlue>(blueFactory, blueFire)