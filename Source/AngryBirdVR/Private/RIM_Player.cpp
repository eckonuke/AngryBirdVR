// Fill out your copyright notice in the Description page of Project Settings.


#include "RIM_Player.h"
#include <Components/CapsuleComponent.h>
#include <Camera/CameraComponent.h>
#include <MotionControllerComponent.h>
#include <Components/SkeletalMeshComponent.h>
#include "RIM_MoveComponent.h"
#include "EnhancedInputComponent.h"
#include "RIM_BirdBlue.h"
#include <../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputSubsystems.h>
#include <Components/TextRenderComponent.h>
#include "BirdSkill.h"

// Sets default values
ARIM_Player::ARIM_Player()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//[�÷��̾�]
	//GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision); //��ü �浹 ������Ʈ. ���ݸ���. CapsuleComponent ��Ŭ��� �ڡڡ�Ȯ�� �ʿ�. �ʿ� ���� �� ������ Ȥ�� ���� �ۼ�

	//[ī�޶�]
	//ī�޶�
	compCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera")); //�÷��̾ ������Ʈ �߰�. CameraComponent ��Ŭ���
	compCamera->SetupAttachment(RootComponent); //��Ʈ������Ʈ �ڽ����� ����
	compCamera->SetRelativeLocation(FVector(-20, 0, 0)); //���ʿ� �� ���� ����
	//�޽�
// 	ConstructorHelpers::FObjectFinder<UStaticMesh> tempCamera(TEXT("/Script/Engine.StaticMesh'/Engine/EditorMeshes/MatineeCam_SM.MatineeCam_SM'"));
// 	if (tempCamera.Succeeded())
// 	{
// 		meshCamera->SetStaticMesh(tempCamera.Object);
// 	}
// 	meshCamera->SetCollisionEnabled(ECollisionEnabled::NoCollision); //�޽� ���ݸ���

	//[�޼�]
	//��Ʈ�ѷ�
	compLeftCon = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("LeftController")); //�÷��̾ ������Ʈ �߰�
	compLeftCon->SetupAttachment(RootComponent); //��Ʈ������Ʈ �ڽ����� ����
 	//�޽�(���̷�Ż)
 	meshLeftHand = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SlingShot")); //�÷��̾ �޽� ������Ʈ �߰�. SkeletalMeshComponent ��Ŭ���
 	meshLeftHand->SetupAttachment(compLeftCon); //�޼� ��Ʈ�ѷ� �ڽ����� ����
 	ConstructorHelpers::FObjectFinder<USkeletalMesh> tempLeftHand(TEXT("/Script/Engine.SkeletalMesh'/Game/Characters/MannequinsXR/Meshes/SKM_MannyXR_left.SKM_MannyXR_left'")); //������ �⺻ ���� ���. ���� ����
 	if (tempLeftHand.Succeeded())
 	{
 		meshLeftHand->SetSkeletalMesh(tempLeftHand.Object);
 	}
 	meshLeftHand->SetCollisionEnabled(ECollisionEnabled::NoCollision); //�޽� ���ݸ���
 	meshLeftHand->SetRelativeLocation(FVector(0, -20, 0)); //���ʿ� �� ���� ���� 
 	meshLeftHand->SetRelativeRotation(FRotator(-25.0f, 180.0f, 90.0f)); //���ʿ� �� ���� ���� 

	//�޽�(�׽�Ʈ��)
// 	meshLeftHand = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SlingShot")); //�÷��̾ �޽� ������Ʈ �߰�. SkeletalMeshComponent ��Ŭ���
// 	meshLeftHand->SetupAttachment(compLeftCon); //�޼� ��Ʈ�ѷ� �ڽ����� ����
// 	ConstructorHelpers::FObjectFinder<USkeletalMesh> tempLeftHand(TEXT("/Script/Engine.SkeletalMesh'/Game/FPWeapon/Mesh/SK_FPGun.SK_FPGun'")); //������ �⺻ ���� ���. ���� ����
// 	if (tempLeftHand.Succeeded())
// 	{
// 		meshLeftHand->SetSkeletalMesh(tempLeftHand.Object);
// 	}
// 	meshLeftHand->SetCollisionEnabled(ECollisionEnabled::NoCollision); //�޽� ���ݸ���
// 	meshLeftHand->SetRelativeLocation(FVector(0, -20, 0)); //���ʿ� �� ���� ���� 
// 	meshLeftHand->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f)); //���ʿ� �� ���� ���� 
// 	meshLeftHand->SetRelativeScale3D(FVector(0.5f)); //���ʿ� �� ���� ���� 
	
 	//�޽�(����ƽ)
	//meshLeftHand = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LeftHand")); //�÷��̾ �޽� ������Ʈ �߰�. StaticMeshComponent ��Ŭ���
	//meshLeftHand->SetupAttachment(compLeftCon); //�޼� ��Ʈ�ѷ� �ڽ����� ����
	//ConstructorHelpers::FObjectFinder<UStaticMesh> tempLeftHand(TEXT("/Script/Engine.StaticMesh'/Game/Resource/Test_SlingShot/SlingShot_01/Source/Slingshot2.Slingshot2'")); //������ ����
	//if (tempLeftHand.Succeeded())
	//{
	//	meshLeftHand->SetStaticMesh(tempLeftHand.Object);
	//}
	//meshLeftHand->SetCollisionEnabled(ECollisionEnabled::NoCollision); //�޽� ���ݸ���
	//meshLeftHand->SetRelativeLocation(FVector(20, 0, -15)); //���ʿ� �� ���� ����
	//meshLeftHand->SetRelativeRotation(FRotator(0.0f, 90.0f, -30.0f)); //���ʿ� �� ���� ����
	//meshLeftHand->SetRelativeScale3D(FVector(0.18f)); //���ʿ� �� ���� ����
	//�α�(Ȯ�ο�)
	logLeft = CreateDefaultSubobject<UTextRenderComponent>(TEXT("LeftLogText"));
	logLeft->SetupAttachment(compLeftCon);
	logLeft->SetRelativeRotation(FRotator(0.0f, 180.0f, 0.0f)); //�ؽ�Ʈ 180 ����
	logLeft->SetTextRenderColor(FColor::Yellow);
	logLeft->SetHorizontalAlignment(EHTA_Center);
	//logLeft >SetVerticalAlignment(EVRTA_TextCenter);
	//��� �ҽ� ����
	compLeftCon->MotionSource = "Left"; //�ڡڡ�???

	//[������]
	//��Ʈ�ѷ�
	compRightCon = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("RightController")); //�÷��̾ ������Ʈ �߰�. MotionControllerComponent ��Ŭ���
	compRightCon->SetupAttachment(RootComponent); //��Ʈ������Ʈ �ڽ����� ����
	//�޽�
	meshRightHand = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("RightHand")); //�÷��̾ �޽� ������Ʈ �߰�. SkeletalMeshComponent ��Ŭ���. �����ĺ���(���� ���̷�Ż�޽�)
	meshRightHand->SetupAttachment(compRightCon); //������ ��Ʈ�ѷ� �ڽ����� ����
	ConstructorHelpers::FObjectFinder<USkeletalMesh> tempRihgtHand(TEXT("/Script/Engine.SkeletalMesh'/Game/Characters/MannequinsXR/Meshes/SKM_MannyXR_right.SKM_MannyXR_right'")); //�����ĺ���(���� ���̷�Ż�޽�)
	if (tempRihgtHand.Succeeded())
	{
		meshRightHand->SetSkeletalMesh(tempRihgtHand.Object);
	}
	meshRightHand->SetCollisionEnabled(ECollisionEnabled::NoCollision); //�޽� ���ݸ���
	//meshLeftHand->SetRelativeLocation(FVector(0, 20, 0)); //���ʿ� �� ���� ����
	meshRightHand->SetRelativeRotation(FRotator(25.0f, 0.0f, 90.0f)); //���ʿ� �� ���� ����
	//�α�(Ȯ�ο�)
	logRight = CreateDefaultSubobject<UTextRenderComponent>(TEXT("RightLogText"));
	logRight->SetupAttachment(compRightCon);
	logRight->SetRelativeRotation(FRotator(0.0f, 180.0f, 0.0f)); //�ؽ�Ʈ 180 ����
	logRight->SetTextRenderColor(FColor::Yellow);
	logRight->SetHorizontalAlignment(EHTA_Center);
	//logRight > SetVerticalAlignment(EVRTA_TextCenter);
	//��� �ҽ� ����
	compRightCon->MotionSource = "Right"; //�ڡڡ�???

	//[��Ʈ�ѷ�]
	//axis ���� �̿��ؼ� ĳ����(��Ʈ�ѷ�)�� ȸ���Ѵ�
	bUseControllerRotationPitch = true; //�ڡڡ�???

	//�ڡڡ�???
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	//�Ķ��� Ŭ���� �����ͼ� ���. ���� ���ϴ� ���� �����Ϸ��� �Ķ����� ������ ��� ����...? �ڡڡڿ켱 �Ķ����� ���� ---> �׽�Ʈ
	ConstructorHelpers::FClassFinder<ARIM_BirdBlue> tempBlue(TEXT("/Script/Engine.Blueprint'/Game/BluePrints/BP_BirdBlue.BP_BirdBlue_C'")); // �������Ʈ ���. _C'
	if (tempBlue.Succeeded())
	{
		blueFactory = tempBlue.Class; //BP_BirdBlue ���� ��
	}



	//[�÷��̾ ���� ������Ʈ �߰�]
	//MoveComponent �߰�
	compMove = CreateDefaultSubobject<URIM_MoveComponent>(TEXT("MoveComponent"));

	//BirdSkillComponent �߰�
	//compSkill = CreateDefaultSubobject<UBirdSkill>(TEXT("SkillComponent"));

	//�߻�Component �߰�
	//���ϴ� �ڵ�


}

// Called when the game starts or when spawned
void ARIM_Player::BeginPlay()
{
	Super::BeginPlay();

	//1. �÷��̾� ��Ʈ�ѷ��� �����´�.
	APlayerController* playerCon = GetWorld()->GetFirstPlayerController();

	//2. �÷��̾� ��Ʈ�ѷ����� EnhancedInputLocalPlayerSubsystem �� �����´�.
	UEnhancedInputLocalPlayerSubsystem* subsys = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(playerCon->GetLocalPlayer());

	//3. ������ Subsystem �� IMC �� ����Ѵ�.(�켱���� 0��)
	subsys->AddMappingContext(vrMapping, 0);

	//[��(�Ѿ�) ����]
// 	//���� �����Ѵ�
// 	blueBird = GetWorld()->SpawnActor<ARIM_BirdBlue>(birdFactory, GetActorLocation(), GetActorRotation());
// 	//������ ���� ��Ȱ��ȭ�Ѵ�
// 	blueBird->SetActive(false);
// 	//������ ���� arrayBlueBird �� �߰�
// 	arrayBlueBird.Add(blueBird);




	
	//���� ������ �� ��(�Ѿ�)�� �� ���δ� �ڡڡڻ��ѿ��� �� ���δ�
	//blueBird->meshBlue->SetVisibility(false);
	
	//���� �ð� ���� �� ù��° �� ����
// 	FTimerHandle settingTimer;
// 	GetWorld()->GetTimerManager().SetTimer(settingTimer, this, &ARIM_Player::birdSetting, delaySettingTime, false); //Ÿ�̸�

}

// Called every frame
void ARIM_Player::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ARIM_Player::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//[Enhanced Action Events]
	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	if (EnhancedInputComponent != nullptr)
	{
		//�̵� �Լ� ���� ---> ������ Ʈ����
		compMove->SetupPlayerInputComponent(EnhancedInputComponent);

		//��ų �Լ� ���� ---> ������ �׸� �ڡڡڽ��� ���ӿ����� ������ Ʈ���� ���
		//compSkill->SetupPlayerInputComponent(EnhancedInputComponent);
		
		//�߻� �Լ� ���� ---> ���� Ʈ���� �̸� ���� �ڵ� �߰� �ʿ�...?
		//���ϴ� �ڵ�



		//������ �׸� ---> �� ��ų ��� �ڡڡڽ��� ���ӿ����� ������ Ʈ���� ��� ---> �׽�Ʈ
		EnhancedInputComponent->BindAction(rightGrip, ETriggerEvent::Started, this, &ARIM_Player::inputSkill);

		

	}




}


	//���� �ð� ���� �� ù��° �� ����
// void ARIM_Player::birdSetting()
// {
// 	//blueBird->meshBlue->SetVisibility(true);
// }

//��ų ��� ---> �׽�Ʈ
void ARIM_Player::inputSkill()
{
	FString msg = FString(__FUNCTION__); //Ȯ�ο� �α�
	logRight->SetText(FText::FromString(msg)); //Ȯ�ο� �α�

	FRotator actorRot;


	//GetWorld()->SpawnActor<ARIM_BirdBlue>(blueFactory, birdBlue->GetActorLocation() + birdBlue->GetActorForwardVector() * 200, actorRot.Yaw);


	//GetWorld()->SpawnActor<ARIM_BirdBlue>(blueFactory, birdBlue->GetActorLocation() + birdBlue->GetActorForwardVector() * 200, birdBlue->GetActorRotation());

	GetWorld()->SpawnActor<ARIM_BirdBlue>(blueFactory, GetActorLocation() + GetActorForwardVector() * 200, GetActorRotation());
	actorRot = GetActorRotation();
	actorRot.Yaw -= 30;
	GetWorld()->SpawnActor<ARIM_BirdBlue>(blueFactory, GetActorLocation() + GetActorForwardVector() * 200, actorRot);
	actorRot = GetActorRotation();
	actorRot.Yaw += 30;
	GetWorld()->SpawnActor<ARIM_BirdBlue>(blueFactory, GetActorLocation() + GetActorForwardVector() * 200, actorRot);


}

void ARIM_Player::PredictionPath() {

}