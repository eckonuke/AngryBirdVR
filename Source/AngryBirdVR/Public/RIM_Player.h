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
	UPROPERTY(EditAnywhere)
	class UCameraComponent* compCamera;
	//�޽�
	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* meshCamera;

	//[�޼�/����]
	//��� ��Ʈ�ѷ�
	UPROPERTY(EditAnywhere)
	class UMotionControllerComponent* compLeftCon;
	//�޽�
 	UPROPERTY(EditAnywhere)
 	class USkeletalMeshComponent* meshLeftHand; //�����̷�Ż�޽�
/* 	UPROPERTY(EditAnywhere)
 	class UStaticMeshComponent* meshLeftHand;*/ //������ƽ�޽�
	//�α�
	UPROPERTY(EditAnywhere)
	class UTextRenderComponent* logLeft;

	//[������]
	//��� ��Ʈ�ѷ�
	UPROPERTY(EditAnywhere)
	class UMotionControllerComponent* compRightCon;
	//�޽�
	UPROPERTY(EditAnywhere)
	class USkeletalMeshComponent* meshRightHand; //�����̷�Ż�޽�
	//�α�
	UPROPERTY(EditAnywhere)
	class UTextRenderComponent* logRight;

public:
	//��� ����� ���� ��ġ ����
	//UPROPERTY(EditAnywherer)
	//TEnumAsByte<enum EHMDTrackingOrigin::Type> trackOrigin;

public:
	//Input Mapping Context. �������Ʈ���� ���� IMC_MyVRMapping
	UPROPERTY(EditAnywhere)
	class UInputMappingContext* vrMapping;

	//Input Action. ������ �׸�. �� ��ų ��� �ڡڡڽ��� ���ӿ����� ������ Ʈ���� ��� ---> �׽�Ʈ
	UPROPERTY(EditAnyWhere)
	class UInputAction* rightGrip;

	//�Ķ��� ��ų ---> �׽�Ʈ
	UPROPERTY(EditAnywhere)
	class UInputAction* rightA;

	//������ ��ų ---> �׽�Ʈ
	UPROPERTY(EditAnywhere)
	class UInputAction* rightB;


public:
	//[�÷��̾ ����������Ʈ �߰�]
	//MoveComponent �� Player �� �߰�
	UPROPERTY(EditAnywhere)
	class URIM_MoveComponent* compMove;

	//�߻�Component �� Player �� �߰�
	//UPROPERTY(EditAnywhere)
	//���ϴ� �ڵ�


 public:
 	//�Ķ���
	UPROPERTY()
	class ARIM_BirdBlue* birdBlue;

	//�Ķ���(�Ѿ�)
 	UPROPERTY(EditAnywhere)
 	TSubclassOf<class ARIM_BirdBlue> blueFactory;

	//������
	UPROPERTY()
	class ARIM_BirdBlack* birdBlack;

	//������(�Ѿ�)
	UPROPERTY(EditAnywhere)
	TSubclassOf<class ARIM_BirdBlack> blackFactory;


public:
	//��ų ���
	void InputSkill();

	//�Ķ��� ��ų
	void BlueSkill();

	//������ ��ų
	void BlackSkill();

	void PredictionPath();
};