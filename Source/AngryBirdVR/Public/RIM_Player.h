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
	//�޽�
 	UPROPERTY(EditAnywhere, BlueprintReadWrite)
 	class UStaticMeshComponent* meshLeftHand; //�����̷�Ż�޽�
/* 	UPROPERTY(EditAnywhere)
 	class UStaticMeshComponent* meshLeftHand;*/ //������ƽ�޽�
	//�α�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UTextRenderComponent* logLeft;
	//��Ʈ�ѷ��� ���� ������(��)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UWidgetInteractionComponent* compWidgetPointer_left;

	//[������]
	//��� ��Ʈ�ѷ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UMotionControllerComponent* compRightCon;
	//�޽�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USkeletalMeshComponent* meshRightHand; //�����̷�Ż�޽�
	//�α�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UTextRenderComponent* logRight;
	//��Ʈ�ѷ��� ���� ������(��)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UWidgetInteractionComponent* compWidgetPointer_right;

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
	//�߻� ��ҹ�ư
	UPROPERTY(EditAnywhere)
	class UInputAction* leftX;
	//�÷��̾� ȸ�� Ű
	UPROPERTY(EditAnywhere)
		class UInputAction* rightThumbstick;

public:
	//[�÷��̾ ����������Ʈ �߰�]
	//MoveComponent �� Player �� �߰�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class URIM_MoveComponent* compMove;

	//WidgetPointerComponent �� Player �� �߰�. (����! ������ �����ͷ� �����Ѽ� ������. ������ ������ �ƴ�)
	UPROPERTY(EditAnywhere)
	class URIM_WidgetPointerComponent* widgetComp; //RIM_WidgetPointerComponent ������Ʈ. �����Ͱ� �۵��ϱ� ���� �ʿ� ---> ���ϴ� �߰�
	//�߻�Component �� Player �� �߰�
	//UPROPERTY(EditAnywhere)
	//���ϴ� �ڵ�
	//�Ҹ� �߰�
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
	//���� ---> ���ϴ� �߰�
	UPROPERTY()
	class AKYI_AngryRed* birdRed;
	//����(�Ѿ�) ---> ���ϴ� �߰�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class AKYI_AngryRed> redFactory;
	//���� ---> ���ϴ� �߰�
	UPROPERTY()
	class AKYI_AngryChuck* birdYellow;
	//����(�Ѿ�) ---> ���ϴ� �߰�
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
	//��� ���� ---> ���ϴ� �߰�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class APredictionObject> pathFactory;
	//��ƽ �ǵ��
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UHapticFeedbackEffect_Base* grabHaptic;

public:
	//�÷��̾� ȸ��
	void RotateAxis(const struct FInputActionValue& value);
	//��ų ���
	void InputSkill();
	//�Ķ��� ��ų
	void BlueSkill();
	//����� ��ų ---> ���ϴ� �߰�
	void YellowSkill();
	//������ ��ų
	void BlackSkill();
	//�߻� �غ� ---> ���ϴ� �߰�
	void readyShoot();
	//�߻� ---> ���ϴ� �߰�
	void shootBird();
	//�߻� ��� ---> ���ϴ� �߰�
	void cancelShoot();
	//�Ҹ� ���
	void playSound(class USoundBase* sound);
	//��Ʈ�ѷ� ��ƽ �ǵ��
	void rightConHaptic();

	//�Ʒ� �ڵ� ���ϴ� �߰�
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
	//�Ʒ� �ڵ� ���ϴ� �߰�
	bool bShouldPredict = false;
	bool bWillShoot = true;
	FVector rightHandPosition;
	FVector fireVelocity;

	//�� ���� ���
	void birdCalc();
};