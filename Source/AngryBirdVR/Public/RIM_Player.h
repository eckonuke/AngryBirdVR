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
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UCameraComponent* compCamera;
	//메시
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* meshCamera;

	//[왼손/새총]
	//모션 컨트롤러
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UMotionControllerComponent* compLeftCon;
	//메시
 	UPROPERTY(EditAnywhere, BlueprintReadWrite)
 	class UStaticMeshComponent* meshLeftHand; //▶스켈레탈메시
/* 	UPROPERTY(EditAnywhere)
 	class UStaticMeshComponent* meshLeftHand;*/ //▶스태틱메시
	//로그
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UTextRenderComponent* logLeft;
	//컨트롤러에 붙인 포인터(선)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UWidgetInteractionComponent* compWidgetPointer_left;

	//[오른손]
	//모션 컨트롤러
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UMotionControllerComponent* compRightCon;
	//메시
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USkeletalMeshComponent* meshRightHand; //▶스켈레탈메시
	//로그
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UTextRenderComponent* logRight;
	//컨트롤러에 붙인 포인터(선)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UWidgetInteractionComponent* compWidgetPointer_right;

public:
	//헤드 장비의 기준 위치 설정
	//UPROPERTY(EditAnywherer)
	//TEnumAsByte<enum EHMDTrackingOrigin::Type> trackOrigin;

public:
	//Input Mapping Context. 블루프린트에서 만든 IMC_MyVRMapping
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UInputMappingContext* vrMapping;

	//Input Action. 오른손 그립. 새 스킬 사용 ★★★실제 게임에서는 오른손 트리거 사용 ---> 테스트
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	class UInputAction* rightGrip;

	//파란새 스킬 ---> 테스트
	UPROPERTY(EditAnywhere)
	class UInputAction* rightA;

	//검은새 스킬 ---> 테스트
	UPROPERTY(EditAnywhere)
	class UInputAction* rightB;
	//발사 취소버튼
	UPROPERTY(EditAnywhere)
	class UInputAction* leftX;
	//플레이어 회전 키
	UPROPERTY(EditAnywhere)
		class UInputAction* rightThumbstick;

public:
	//[플레이어에 액터컴포넌트 추가]
	//MoveComponent 를 Player 에 추가
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class URIM_MoveComponent* compMove;

	//WidgetPointerComponent 를 Player 에 추가. (위젯! 레이저 포인터로 가르켜서 누른다. 레이저 포인터 아님)
	UPROPERTY(EditAnywhere)
	class URIM_WidgetPointerComponent* widgetComp; //RIM_WidgetPointerComponent 컴포넌트. 포인터가 작동하기 위해 필요 ---> 용일님 추가
	//발사Component 를 Player 에 추가
	//UPROPERTY(EditAnywhere)
	//용일님 코드
	//소리 추가
	UPROPERTY(EditAnywhere)
	class USoundBase* redSound;
	UPROPERTY(EditAnywhere)
	class USoundBase* blueSound;
	UPROPERTY(EditAnywhere)
	class USoundBase* yellowSound;
	UPROPERTY(EditAnywhere)
	class USoundBase* slingSound;
	UPROPERTY(EditAnywhere)
	class USoundBase* exploSound;

 public:
	//레드 ---> 용일님 추가
	UPROPERTY()
	class AKYI_AngryRed* birdRed;
	//레드(총알) ---> 용일님 추가
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class AKYI_AngryRed> redFactory;
	//옐로 ---> 용일님 추가
	UPROPERTY()
	class AKYI_AngryChuck* birdYellow;
	//옐로(총알) ---> 용일님 추가
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class AKYI_AngryChuck> yellowFactory;
 	//파란새
	UPROPERTY()
	class ARIM_BirdBlue* birdBlue;
	//파란새(총알)
 	UPROPERTY(EditAnywhere, BlueprintReadWrite)
 	TSubclassOf<class ARIM_BirdBlue> blueFactory;
	//검은새
	UPROPERTY()
	class ARIM_BirdBlack* birdBlack;
	//검은새(총알)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class ARIM_BirdBlack> blackFactory;
	//경로 공장 ---> 용일님 추가
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class APredictionObject> pathFactory;
	//햅틱 피드백
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UHapticFeedbackEffect_Base* grabHaptic;

public:
	//플레이어 회전
	void RotateAxis(const struct FInputActionValue& value);
	//스킬 사용
	void InputSkill();
	//파란새 스킬
	void BlueSkill();
	//노란새 스킬 ---> 용일님 추가
	void YellowSkill();
	//검은새 스킬
	void BlackSkill();
	//발사 준비 ---> 용일님 추가
	void readyShoot();
	//발사 ---> 용일님 추가
	void shootBird();
	//발사 취소 ---> 용일님 추가
	void cancelShoot();
	//소리 재생
	void playSound(class USoundBase* sound);
	//컨트롤러 햅틱 피드백
	void rightConHaptic();

	//아래 코드 용일님 추가
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 score = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 redCount = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 blueCount = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 yellowCount = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 blackCount = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 birdCount = redCount + yellowCount + blueCount + blackCount;

	bool finish = false;

private:
	//아래 코드 용일님 추가
	bool bShouldPredict = false;
	bool bWillShoot = true;
	FVector rightHandPosition;
	FVector fireVelocity;

	//새 갯수 계산
	void birdCalc();
};