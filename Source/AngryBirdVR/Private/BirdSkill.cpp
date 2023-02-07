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

	//�Ķ��� Ŭ������ �����´�
// 	ConstructorHelpers::FClassFinder<ARIM_BirdBlue> tempBlue(TEXT("/Script/Engine.Blueprint'/Game/BluePrints/BP_BirdBlue.BP_BirdBlue_C'")); // �������Ʈ ���. _C'
// 	if (tempBlue.Succeeded())
// 	{
// 		blueFactory = tempBlue.Class; //BP_BirdBlue ���� ��
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


//[SetupPlayerInputComponent] �����ռ�
void UBirdSkill::SetupPlayerInputComponent(class UEnhancedInputComponent* PlayerInputComponent)
{
	//Super::SetupPlayerInputComponent(PlayerInputComponent); //�ڡڡڴٸ� ���Ͽ��� �����Լ� ���� �� Super ����ߴµ� ���� �ʿ� ���°ž�? ��?

	//������ �׸� ---> �� ��ų ��� �ڡڡڽ��� ���ӿ����� ������ Ʈ���� ���
	//PlayerInputComponent->BindAction(rightGrip, ETriggerEvent::Started, this, &UBirdSkill::inputSkill);
	



}


// void UBirdSkill::inputSkill()
// {
// 	FString msg = FString(__FUNCTION__); //Ȯ�ο� �α�
// 	player->logRight->SetText(FText::FromString(msg)); //Ȯ�ο� �α�
// 
// 
// 	//���� ���ѿ� �Ķ����� ���̴� ���¸�...? ���� ���ѿ� �Ķ����� �����Ǹ�...?
// 	//if (player->meshLeftHand->IsVisible() == true)
// 		
// 	FRotator actorRot;
// 	actorRot = birdBlue->GetActorRotation();
// 	actorRot.Yaw -= 30;
// 
// 	//���� �Ķ��� ��ġ���� �Ķ��� 1������ �����Ѵ�. ���� �Ķ������� ���ʹ���(ȸ��Yaw-30)���� ����
// 	// �߻�ȴ�. ���ư���
// 	//GetWorld()->SpawnActor<ARIM_BirdBlue>(blueFactory, birdBlue->GetActorLocation() + birdBlue->GetActorForwardVector() * 200, actorRot.Yaw);
// 	//GetWorld()->SpawnActor<ARIM_BirdBlue>(blueFactory, birdBlue->GetActorLocation() + birdBlue->GetActorForwardVector() * 200, birdBlue->GetActorRotation());
// 	  
// 	//���� �Ķ��� ��ġ���� �Ķ��� 1������ �����Ѵ�. /���� �Ķ������� �����ʹ���(ȸ��Yaw+30)���� ����
// 	// �߻�ȴ�. ���ư���
// 
// }








//blueBirdPos Transform �� �����´�
//player->meshLeftHand->GetSocketTransform(TEXT("BlueSkillPos")); //���������� �ϴ� ���� �̸� �ִ´�
//FTransform blueFire = player->meshLeftHand->GetSocketTransform(TEXT("BlueSkillPos"));

//�Ķ��� ����(��ġ, ȸ�� ����)
//���忡�� �Ķ��� �����´�
//GetWorld()->SpawnActor<ARIM_BirdBlue>(blueFactory, blueFire)