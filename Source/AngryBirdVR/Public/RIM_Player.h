// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "RIM_BirdBlue.h"
#include "RIM_Player.generated.h"

UCLASS()
class ANGRYBIRDVR_API ARIM_Player : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ARIM_Player();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	//[카메라]
	//카메라
	UPROPERTY(EditAnywhere)
	class UCameraComponent* compCamera;
	//메시
	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* meshCamera;

	//[왼손/새총]
	//모션 컨트롤러
	UPROPERTY(EditAnywhere)
	class UMotionControllerComponent* compLeftCon;
	//메시
 	//UPROPERTY(EditAnywhere)
 	//class USkeletalMeshComponent* meshLeftHand; //▶스켈레탈메시
 	UPROPERTY(EditAnywhere)
 	class UStaticMeshComponent* meshLeftHand; //▶스태틱메시
	//로그
	UPROPERTY(EditAnywhere)
	class UTextRenderComponent* logLeft;

	//[오른손]
	//모션 컨트롤러
	UPROPERTY(EditAnywhere)
	class UMotionControllerComponent* compRightCon;
	//메시
	UPROPERTY(EditAnywhere)
	class USkeletalMeshComponent* meshRightHand; //▶스켈레탈메시
	//로그
	UPROPERTY(EditAnywhere)
	class UTextRenderComponent* logRight;

public:
	//헤드 장비의 기준 위치 설정
	//UPROPERTY(EditAnywherer)
	//TEnumAsByte<enum EHMDTrackingOrigin::Type> trackOrigin;

public:
	//Input Mapping Context. 블루프린트에서 만든 IMC_MyVRMapping
	UPROPERTY(EditAnywhere)
	class UInputMappingContext* vrMapping;

	//Input Action. 오른손 그립 ★★★실제 게임에서는 오른손 트리거 사용 ---> 테스트
	UPROPERTY(EditAnyWhere)
	class UInputAction* rightGrip;


public:
	//[플레이어에 액터컴포넌트 추가]
	//MoveComponent 를 Player 에 추가
	UPROPERTY(EditAnywhere)
	class URIM_MoveComponent* compMove;

	//BirdSkillComponent 를 Player 에 추가
	//UPROPERTY(EditAnywhere)
	//class UBirdSkill* compSkill;

	//발사Component 를 Player 에 추가
	//UPROPERTY(EditAnywhere)
	//용일님 코드

 public:
 	//파란새
	class ARIM_BirdBlue* birdBlue;

	//파란새(총알)
 	UPROPERTY(EditAnywhere)
 	TSubclassOf<class ARIM_BirdBlue> blueFactory;



	//새 세팅 딜레이 시간
	//UPROPERTY(EditAnywhere)
	//float delaySettingTime = 5.0f;

	//일정 시간 지난 후 첫번째 새 노출
	//void birdSetting();


public:
	//스킬 사용 ---> 테스트
	void inputSkill();

};