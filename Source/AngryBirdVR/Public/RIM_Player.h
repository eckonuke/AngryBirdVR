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
	//[ī�޶�]
	//ī�޶�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UCameraComponent* compCamera;
	//�޽�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* meshCamera;

	//[�޼�/����]
	//��� ��Ʈ�ѷ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UMotionControllerComponent* compLeftCon;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UWidgetInteractionComponent* compWidgetPointer_left;
	//�޽�
 	UPROPERTY(EditAnywhere, BlueprintReadWrite)
 	class UStaticMeshComponent* meshLeftHand; //�����̷�Ż�޽�
/* 	UPROPERTY(EditAnywhere)
 	class UStaticMeshComponent* meshLeftHand;*/ //������ƽ�޽�
	//�α�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UTextRenderComponent* logLeft;

	//[������]
	//��� ��Ʈ�ѷ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UMotionControllerComponent* compRightCon;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UWidgetInteractionComponent* compWidgetPointer_right;
		
	//�޽�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USkeletalMeshComponent* meshRightHand; //�����̷�Ż�޽�
	//�α�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UTextRenderComponent* logRight;

public:
	//��� ����� ���� ��ġ ����
	//UPROPERTY(EditAnywherer)
	//TEnumAsByte<enum EHMDTrackingOrigin::Type> trackOrigin;

public:
	//Input Mapping Context. �������Ʈ���� ���� IMC_MyVRMapping
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UInputMappingContext* vrMapping;

	//Input Action. ������ �׸�. �� ��ų ��� �ڡڡڽ��� ���ӿ����� ������ Ʈ���� ��� ---> �׽�Ʈ
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	class UInputAction* rightGrip;

	//�Ķ��� ��ų ---> �׽�Ʈ
	UPROPERTY(EditAnywhere)
	class UInputAction* rightA;

	//������ ��ų ---> �׽�Ʈ
	UPROPERTY(EditAnywhere)
	class UInputAction* rightB;
	UPROPERTY(EditAnywhere)
	class UInputAction* leftX;

public:
	//[�÷��̾ ����������Ʈ �߰�]
	//MoveComponent �� Player �� �߰�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class URIM_MoveComponent* compMove;
	//WidgetPointerComponent �� Player �� �߰�. (����. ������ �����ͷ� �����Ѽ� ������)
	UPROPERTY(EditAnywhere)
		class URIM_WidgetPointerComponent* widgetComp;
	//�߻�Component �� Player �� �߰�
	//UPROPERTY(EditAnywhere)
	//���ϴ� �ڵ�
	UPROPERTY(EditAnywhere)
	class USoundBase* slingSound;
	UPROPERTY(EditAnywhere)
		class USoundBase* redSound;
	UPROPERTY(EditAnywhere)
		class USoundBase* blueSound;
	UPROPERTY(EditAnywhere)
		class USoundBase* yellowSound;

 public:
	 //�Ķ���
	 UPROPERTY()
		 class AKYI_AngryRed* birdRed;
	 //�Ķ���(�Ѿ�)
	 UPROPERTY(EditAnywhere, BlueprintReadWrite)
		 TSubclassOf<class AKYI_AngryRed> redFactory;
	 //�Ķ���
	 UPROPERTY()
		 class AKYI_AngryChuck* birdYellow;
	 //�Ķ���(�Ѿ�)
	 UPROPERTY(EditAnywhere, BlueprintReadWrite)
		 TSubclassOf<class AKYI_AngryChuck> yellowFactory;
 	//�Ķ���
	UPROPERTY()
	class ARIM_BirdBlue* birdBlue;
	//�Ķ���(�Ѿ�)
 	UPROPERTY(EditAnywhere, BlueprintReadWrite)
 	TSubclassOf<class ARIM_BirdBlue> blueFactory;
	//������
	UPROPERTY()
	class ARIM_BirdBlack* birdBlack;
	//������(�Ѿ�)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class ARIM_BirdBlack> blackFactory;

	//��� ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class APredictionObject> pathFactory;
public:
	//��ų ���
	void InputSkill();
	//�Ķ��� ��ų
	void BlueSkill();
	//����� ��ų
	void YellowSkill();
	//������ ��ų
	void BlackSkill();
	//�߻� �غ�
	void readyShoot();
	//�߻�
	void shootBird();
	//�߻� ���
	void cancelShoot();
	//���� ���󰥶� �Ҹ�
	void playSound(class USoundBase* sound);

	float score = 0;
	int32 birdCount = 3;
	int32 redCount = 1;
	int32 blueCount = 1;
	int32 yellowCount = 1;
	int32 blackCount = 1;
private:
	bool bShouldPredict = false;
	bool bWillShoot = true;
	FVector rightHandPosition;
	FVector fireVelocity;
	float power = 1000;
	float cancelLength = 0;
	float cancelRange = 10;
};