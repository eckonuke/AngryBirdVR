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
 	class USkeletalMeshComponent* meshLeftHand; //▶스켈레탈메시
/* 	UPROPERTY(EditAnywhere)
 	class UStaticMeshComponent* meshLeftHand;*/ //▶스태틱메시
	//로그
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UTextRenderComponent* logLeft;

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


public:
	//[플레이어에 액터컴포넌트 추가]
	//MoveComponent 를 Player 에 추가
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class URIM_MoveComponent* compMove;

	//발사Component 를 Player 에 추가
	//UPROPERTY(EditAnywhere)
	//용일님 코드


 public:
 	//파란새
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
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


public:
	//스킬 사용
	void InputSkill();

	//파란새 스킬
	void BlueSkill();

	//노란새 스킬
	void YellowSkill();

	//검은새 스킬
	void BlackSkill();

private:
	bool bShouldPredict = false;
	FVector rightHandPosition;
	FVector fireVelocity;
	float power = 1000000;
	int32 birdCount = 0;
	int32 redCount = 0;
	int32 blueCount = 0;
	int32 yellowCount = 0;
	int32 blackCount = 0;

	class AKYI_AngryChuck* yellowBird;
};