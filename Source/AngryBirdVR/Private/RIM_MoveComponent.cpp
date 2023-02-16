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

	//플레이어 클레스 캐싱
	player = Cast<ARIM_Player>(GetOwner()); //인클루드
	currentWorld = GetWorld();
	
}


// Called every frame
void URIM_MoveComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bIsShowLine) //만약 라인이 보이면
	{
		DrawMoveLine(); //이동 곡선(이동할 곡선을 화면에 그린다) 함수 실행
	}
	
}


//[SetupPlayerInputComponent] 가상합수
void URIM_MoveComponent::SetupPlayerInputComponent(class UEnhancedInputComponent* PlayerInputComponent)
{
	//Super::SetupPlayerInputComponent(PlayerInputComponent); //★★★다른 파일에서 가상함수 만들 때 Super 사용했는데 여긴 필요 없는거야? 왜?

	//[오른손]
		//오른손 트리거 ---> 이동
		PlayerInputComponent->BindAction(rightTrigger, ETriggerEvent::Started, this, &URIM_MoveComponent::rightTriggerShowLine);
		PlayerInputComponent->BindAction(rightTrigger, ETriggerEvent::Completed, this, &URIM_MoveComponent::rightTriggerHideLine);

	//테스트
// 	PlayerInputComponent->BindAction(rightTrigger, ETriggerEvent::Triggered, this, &URIM_MoveComponent::OnTriggerR);
// 	PlayerInputComponent->BindAction(rightTrigger, ETriggerEvent::Completed, this, &URIM_MoveComponent::OffTriggerR);


}


//오른손 트리거 관련, 이동할 곡선을 화면에 그린다
void URIM_MoveComponent::DrawMoveLine()
{
	//p = p0 + vt - 0.5 * g * t ^ 2
	
	//방향. 왼손 모델링의 로컬 좌표에 맞춰서 forward 방향과 up 방향을 다시 계산하다. 현재 사용한 왼손 모델링에 맞춰...
	FVector handForward = FRotationMatrix(player->meshRightHand->GetComponentRotation()).GetUnitAxis(EAxis::Y); //★현재 모델링한 손의 Y 가 앞방향을 향하고 있기 때문에 손의 Y 를 앞방향으로 만듬
	FVector handUP = FRotationMatrix(player->meshRightHand->GetComponentRotation()).GetUnitAxis(EAxis::X) * -1; //★현재 모델링한 손의 X 가 아래향을 향하고 있기 때문에 손의 X 에 -1 곱해서 위방향으로 만듬
	FVector dir = handForward + handUP;

	//배열 비운다. 왼손 좌표로 돌아오지 않도록...
	lineLocation.Empty();


	for (int32 i = 0; i < lineTimeSegment; i++) //0 ~ 49. 50개
	{
		//시간 t. 소요 시간. 흘러간 시간
		float timeTaken = lineTimeInterval * i; //★★★0.01 * 50

		//p = p0 + vt
		FVector prediction = player->meshRightHand->GetComponentLocation() + dir * power * timeTaken;

		//p.Z -= 0.5 * g * t^2
		prediction.Z += 0.5f * GetWorld()->GetDefaultGravityZ() * timeTaken * timeTaken;

		//배열에 넣는다
		lineLocation.Add(prediction);


		//라인트레이스를 구간마다 체크한다.
		FHitResult hitInfo;

		if (i > 0)
		{
			//if (GetWorld()->LineTraceSingleByProfile(hitInfo, lineLocation[i - 1], lineLocation[i], TEXT("MoveLocation")))
			if (GetWorld()->LineTraceSingleByChannel(hitInfo, lineLocation[i - 1], lineLocation[i], ECC_Visibility))
			{
				position = Cast<ARIM_MoveLocation>(hitInfo.GetActor());
				//부딪힌 지점을 마지막 좌표로 넣고 반복문을 강제 종료한다.
				lineLocation.Add(hitInfo.ImpactPoint);
				break;
			}
		}
	}

	//앞에서 구한 위치 마다 선으로 연결한 그림을 그린다.(DrawLine)
	for (int32 i = 0; i < lineLocation.Num() - 1; i++)//0 ~ 49. 50개
	{
		DrawDebugLine(GetWorld(), lineLocation[i], lineLocation[i + 1], FColor::Green, false, -1, 0, 2); //true 로 할 경우 선이 지워지지 않는다. -1 한 프레임. 2 굵기
	}

}

//오른손 트리거 관련, 순간 이동. 즉시 좌표 변경
void URIM_MoveComponent::Teleport()
{
	//가리킨 지점으로 순간 이동한다.(즉시 좌표 변경)
	FVector targetLoc = lineLocation[lineLocation.Num() - 1]; //100-1
	targetLoc.Z += player->GetCapsuleComponent()->GetScaledCapsuleHalfHeight(); //플레이어가 묻히지 않게 Z 축으로 절반 올린다
	player->SetActorLocation(targetLoc, false, nullptr, ETeleportType::TeleportPhysics);
}

//오른손 트리거 ---> 이동. 라인이 보인다.
void URIM_MoveComponent::rightTriggerShowLine()
{
	FString msg = FString(__FUNCTION__); //확인용 로그
	player->logRight->SetText(FText::FromString(msg)); //확인용 로그

	bIsShowLine = true;
}

//오른손 트리거 ---> 이동. 라인이 안 보이면서 텔레포트 한다.
void URIM_MoveComponent::rightTriggerHideLine()
{
	FString msg = FString(__FUNCTION__); //확인용 로그
	player->logRight->SetText(FText::FromString(msg)); //확인용 로그

	bIsShowLine = false; //라인 안 보인다
	if (position != nullptr) {
		TeleportFade();
		//1초 뒤에 Teleport를 실행해야한다
		FTimerHandle WaitHandle;
		float WaitTime = 1;
		currentWorld->GetTimerManager().SetTimer(WaitHandle, FTimerDelegate::CreateLambda([&]()
			{
				Teleport();
			}), WaitTime, false); //반복도 여기서 추가 변수를 선언해 설정가능
	}
}

// 텔레포트 페이드 인
void URIM_MoveComponent::TeleportFade()
{
	GetWorld()->GetFirstPlayerController()->PlayerCameraManager->StartCameraFade(0, 1.0f, 1.0f, FLinearColor::Black);

	//FTimerHandle fadeTimer; //매개변수. 전달자 용도
	//currentWorld->GetTimerManager().SetTimer(fadeTimer, this, &URIM_MoveComponent::Teleport, 1.0f, false); //타이머
}



//테스트
// void URIM_MoveComponent::OnTriggerR()
// {
//  	FString msg = FString(__FUNCTION__); //확인용 로그
//  	player->logRight->SetText(FText::FromString(msg));
// }
// void URIM_MoveComponent::OffTriggerR()
// {
// 	FString msg = FString(__FUNCTION__); //확인용 로그
// 	player->logRight->SetText(FText::FromString(msg));
//}