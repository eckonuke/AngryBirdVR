// Fill out your copyright notice in the Description page of Project Settings.


#include "RIM_MoveComponent.h"
#include "RIM_Player.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "Components/CapsuleComponent.h"
#include <Components/TextRenderComponent.h>
#include "RIM_MoveLocation.h"



// Sets default values for this component's properties
URIM_MoveComponent::URIM_MoveComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void URIM_MoveComponent::BeginPlay()
{
	Super::BeginPlay();

	//�÷��̾� Ŭ���� ĳ��
	player = Cast<ARIM_Player>(GetOwner()); //��Ŭ���
	currentWorld = GetWorld();
	
}


// Called every frame
void URIM_MoveComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bIsShowLine) //���� ������ ���̸�
	{
		DrawMoveLine(); //�̵� �(�̵��� ��� ȭ�鿡 �׸���) �Լ� ����
	}
	
}


//[SetupPlayerInputComponent] �����ռ�
void URIM_MoveComponent::SetupPlayerInputComponent(class UEnhancedInputComponent* PlayerInputComponent)
{
	//Super::SetupPlayerInputComponent(PlayerInputComponent); //�ڡڡڴٸ� ���Ͽ��� �����Լ� ���� �� Super ����ߴµ� ���� �ʿ� ���°ž�? ��?

	//[������]
		//������ Ʈ���� ---> �̵�
		PlayerInputComponent->BindAction(rightTrigger, ETriggerEvent::Started, this, &URIM_MoveComponent::rightTriggerShowLine);
		PlayerInputComponent->BindAction(rightTrigger, ETriggerEvent::Completed, this, &URIM_MoveComponent::rightTriggerHideLine);

	//�׽�Ʈ
// 	PlayerInputComponent->BindAction(rightTrigger, ETriggerEvent::Triggered, this, &URIM_MoveComponent::OnTriggerR);
// 	PlayerInputComponent->BindAction(rightTrigger, ETriggerEvent::Completed, this, &URIM_MoveComponent::OffTriggerR);


}


//������ Ʈ���� ����, �̵��� ��� ȭ�鿡 �׸���
void URIM_MoveComponent::DrawMoveLine()
{
	//p = p0 + vt - 0.5 * g * t ^ 2
	
	//����. �޼� �𵨸��� ���� ��ǥ�� ���缭 forward ����� up ������ �ٽ� ����ϴ�. ���� ����� �޼� �𵨸��� ����...
	FVector handForward = FRotationMatrix(player->meshRightHand->GetComponentRotation()).GetUnitAxis(EAxis::Y); //������ �𵨸��� ���� Y �� �չ����� ���ϰ� �ֱ� ������ ���� Y �� �չ������� ����
	FVector handUP = FRotationMatrix(player->meshRightHand->GetComponentRotation()).GetUnitAxis(EAxis::X) * -1; //������ �𵨸��� ���� X �� �Ʒ����� ���ϰ� �ֱ� ������ ���� X �� -1 ���ؼ� ���������� ����
	FVector dir = handForward + handUP;

	//�迭 ����. �޼� ��ǥ�� ���ƿ��� �ʵ���...
	lineLocation.Empty();


	for (int32 i = 0; i < lineTimeSegment; i++) //0 ~ 49. 50��
	{
		//�ð� t. �ҿ� �ð�. �귯�� �ð�
		float timeTaken = lineTimeInterval * i; //�ڡڡ�0.01 * 50

		//p = p0 + vt
		FVector prediction = player->meshRightHand->GetComponentLocation() + dir * power * timeTaken;

		//p.Z -= 0.5 * g * t^2
		prediction.Z += 0.5f * GetWorld()->GetDefaultGravityZ() * timeTaken * timeTaken;

		//�迭�� �ִ´�
		lineLocation.Add(prediction);


		//����Ʈ���̽��� �������� üũ�Ѵ�.
		FHitResult hitInfo;

		if (i > 0)
		{
			//if (GetWorld()->LineTraceSingleByProfile(hitInfo, lineLocation[i - 1], lineLocation[i], TEXT("MoveLocation")))
			if (GetWorld()->LineTraceSingleByChannel(hitInfo, lineLocation[i - 1], lineLocation[i], ECC_Visibility))
			{
				position = Cast<ARIM_MoveLocation>(hitInfo.GetActor());
				//�ε��� ������ ������ ��ǥ�� �ְ� �ݺ����� ���� �����Ѵ�.
				lineLocation.Add(hitInfo.ImpactPoint);
				break;
			}
		}
	}

	//�տ��� ���� ��ġ ���� ������ ������ �׸��� �׸���.(DrawLine)
	for (int32 i = 0; i < lineLocation.Num() - 1; i++)//0 ~ 49. 50��
	{
		DrawDebugLine(GetWorld(), lineLocation[i], lineLocation[i + 1], FColor::Green, false, -1, 0, 2); //true �� �� ��� ���� �������� �ʴ´�. -1 �� ������. 2 ����
	}

}

//������ Ʈ���� ����, ���� �̵�. ��� ��ǥ ����
void URIM_MoveComponent::Teleport()
{
	//����Ų �������� ���� �̵��Ѵ�.(��� ��ǥ ����)
	FVector targetLoc = lineLocation[lineLocation.Num() - 1]; //100-1
	targetLoc.Z += player->GetCapsuleComponent()->GetScaledCapsuleHalfHeight(); //�÷��̾ ������ �ʰ� Z ������ ���� �ø���
	player->SetActorLocation(targetLoc, false, nullptr, ETeleportType::TeleportPhysics);
}

//������ Ʈ���� ---> �̵�. ������ ���δ�.
void URIM_MoveComponent::rightTriggerShowLine()
{
	FString msg = FString(__FUNCTION__); //Ȯ�ο� �α�
	player->logRight->SetText(FText::FromString(msg)); //Ȯ�ο� �α�

	bIsShowLine = true;
}

//������ Ʈ���� ---> �̵�. ������ �� ���̸鼭 �ڷ���Ʈ �Ѵ�.
void URIM_MoveComponent::rightTriggerHideLine()
{
	FString msg = FString(__FUNCTION__); //Ȯ�ο� �α�
	player->logRight->SetText(FText::FromString(msg)); //Ȯ�ο� �α�

	bIsShowLine = false; //���� �� ���δ�
	if (position != nullptr) {
		TeleportFade();
		//1�� �ڿ� Teleport�� �����ؾ��Ѵ�
		FTimerHandle WaitHandle;
		float WaitTime = 1;
		currentWorld->GetTimerManager().SetTimer(WaitHandle, FTimerDelegate::CreateLambda([&]()
			{
				Teleport();
			}), WaitTime, false); //�ݺ��� ���⼭ �߰� ������ ������ ��������
	}
}

// �ڷ���Ʈ ���̵� ��
void URIM_MoveComponent::TeleportFade()
{
	GetWorld()->GetFirstPlayerController()->PlayerCameraManager->StartCameraFade(0, 1.0f, 1.0f, FLinearColor::Black);

	//FTimerHandle fadeTimer; //�Ű�����. ������ �뵵
	//currentWorld->GetTimerManager().SetTimer(fadeTimer, this, &URIM_MoveComponent::Teleport, 1.0f, false); //Ÿ�̸�
}



//�׽�Ʈ
// void URIM_MoveComponent::OnTriggerR()
// {
//  	FString msg = FString(__FUNCTION__); //Ȯ�ο� �α�
//  	player->logRight->SetText(FText::FromString(msg));
// }
// void URIM_MoveComponent::OffTriggerR()
// {
// 	FString msg = FString(__FUNCTION__); //Ȯ�ο� �α�
// 	player->logRight->SetText(FText::FromString(msg));
//}