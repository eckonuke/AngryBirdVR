// Fill out your copyright notice in the Description page of Project Settings.


#include "RIM_Player.h"
#include <Components/CapsuleComponent.h>
#include <Camera/CameraComponent.h>
#include <MotionControllerComponent.h>
#include <Components/SkeletalMeshComponent.h>
#include "RIM_MoveComponent.h"
#include "EnhancedInputComponent.h"
#include "KYI_AngryRed.h"
#include "KYI_AngryChuck.h"
#include "RIM_BirdBlue.h"
#include "RIM_BirdBlack.h"
#include <../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputSubsystems.h>
#include <Components/TextRenderComponent.h>
#include <Kismet/GameplayStatics.h>
#include <Components/SphereComponent.h>
#include "PredictionObject.h"
#include <UMG/Public/Components/WidgetInteractionComponent.h>
#include "RIM_WidgetPointerComponent.h"
#include "AngryBirdVR_GameModeBase.h"
#include <Sound/SoundBase.h>

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
	compWidgetPointer_left = CreateDefaultSubobject<UWidgetInteractionComponent>(TEXT("Left Widget Pointer"));
	compWidgetPointer_left->SetupAttachment(compLeftCon);
	////�޽�(���̷�Ż)
	//meshLeftHand = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SlingShot")); //�÷��̾ �޽� ������Ʈ �߰�. SkeletalMeshComponent ��Ŭ���
	//meshLeftHand->SetupAttachment(compLeftCon); //�޼� ��Ʈ�ѷ� �ڽ����� ����
	//ConstructorHelpers::FObjectFinder<USkeletalMesh> tempLeftHand(TEXT("/Script/Engine.SkeletalMesh'/Game/Characters/MannequinsXR/Meshes/SKM_MannyXR_left.SKM_MannyXR_left'")); //������ �⺻ ���� ���. ���� ����
	//if (tempLeftHand.Succeeded())
	//{
	//	meshLeftHand->SetSkeletalMesh(tempLeftHand.Object);
	//}
	//meshLeftHand->SetCollisionEnabled(ECollisionEnabled::NoCollision); //�޽� ���ݸ���
	//meshLeftHand->SetRelativeLocation(FVector(0, -20, 0)); //���ʿ� �� ���� ���� 
	//meshLeftHand->SetRelativeRotation(FRotator(-25.0f, 180.0f, 90.0f)); //���ʿ� �� ���� ���� 

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
	meshLeftHand = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LeftHand")); //�÷��̾ �޽� ������Ʈ �߰�. StaticMeshComponent ��Ŭ���
	meshLeftHand->SetupAttachment(compLeftCon); //�޼� ��Ʈ�ѷ� �ڽ����� ����
	ConstructorHelpers::FObjectFinder<UStaticMesh> tempLeftHand(TEXT("/Script/Engine.StaticMesh'/Game/Resource/Test_SlingShot/SlingShot_01/Source/Slingshot2.Slingshot2'")); //������ ����
	if (tempLeftHand.Succeeded())
	{
		meshLeftHand->SetStaticMesh(tempLeftHand.Object);
	}
	meshLeftHand->SetCollisionEnabled(ECollisionEnabled::NoCollision); //�޽� ���ݸ���
	meshLeftHand->SetRelativeLocation(FVector(0)); //���ʿ� �� ���� ����
	meshLeftHand->SetRelativeRotation(FRotator(0.0f, 90.0f, -90.0f)); //���ʿ� �� ���� ����
	meshLeftHand->SetRelativeScale3D(FVector(0.3f)); //���ʿ� �� ���� ����
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
	compWidgetPointer_right = CreateDefaultSubobject<UWidgetInteractionComponent>(TEXT("Right Widget Pointer"));
	compWidgetPointer_right->SetupAttachment(compRightCon);
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
	ConstructorHelpers::FClassFinder<ARIM_BirdBlue> tempBlue(TEXT("/Script/Engine.Blueprint'/Game/BluePrints/BP_AngryBlue.BP_AngryBlue_C'")); // �������Ʈ ���. _C'
	if (tempBlue.Succeeded())
	{
		blueFactory = tempBlue.Class;
	}

	//������ Ŭ���� �����ͼ� ���
	//ConstructorHelpers::FClassFinder<ARIM_BirdBlue> tempBlack(TEXT("/Script/Engine.Blueprint'/Game/BluePrints/BP_AngryBlack.BP_AngryBlack_C'")); // �������Ʈ ���. _C'
	//if (tempBlack.Succeeded())
	//{
	//	blackFactory = tempBlack.Class;
	//}

	//[�÷��̾ ���� ������Ʈ �߰�]
	//MoveComponent �߰�
	compMove = CreateDefaultSubobject<URIM_MoveComponent>(TEXT("MoveComponent"));
	widgetComp = CreateDefaultSubobject<URIM_WidgetPointerComponent>(TEXT("Widget Component"));
	//�߻�Component �߰�
	//���ϴ� �ڵ�
	ConstructorHelpers::FObjectFinder<USoundBase> tempRedSound(TEXT("/Script/Engine.SoundWave'/Game/Resource/Sound/RedBirdFlySound.RedBirdFlySound'"));
	if (tempRedSound.Succeeded()) {
		redSound = tempRedSound.Object;
	}
	ConstructorHelpers::FObjectFinder<USoundBase> tempBlueSound(TEXT("/Script/Engine.SoundWave'/Game/Resource/Sound/BlueBirdFlySound.BlueBirdFlySound'"));
	if (tempBlueSound.Succeeded()) {
		blueSound = tempBlueSound.Object;
	}
	ConstructorHelpers::FObjectFinder<USoundBase> tempYellowSound(TEXT("/Script/Engine.SoundWave'/Game/Resource/Sound/YellowBirdFlySound.YellowBirdFlySound'"));
	if (tempYellowSound.Succeeded()) {
		yellowSound = tempYellowSound.Object;
	}
	ConstructorHelpers::FObjectFinder<USoundBase> tempSlingSound(TEXT("/Script/Engine.SoundWave'/Game/Resource/Sound/SlingShotStretchSound.SlingShotStretchSound'"));
	if (tempSlingSound.Succeeded()) {
		slingSound = tempSlingSound.Object;
	}
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

	birdCount = 3;

	AAngryBirdVR_GameModeBase* gameMode = Cast<AAngryBirdVR_GameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	gameMode->player = this;

	//���� �ð� ���� �� ù��° �� ����
// 	FTimerHandle settingTimer;
// 	GetWorld()->GetTimerManager().SetTimer(settingTimer, this, &ARIM_Player::birdSetting, delaySettingTime, false); //Ÿ�̸�

}

// Called every frame
void ARIM_Player::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (bShouldPredict) {
		rightHandPosition = compRightCon->GetComponentLocation();
		fireVelocity = (compLeftCon->GetComponentLocation() - rightHandPosition) * 50;
		//FHitResult hitInfo;
		//TArray<FVector> pathPosition;
		//FVector lastTrace;
		//TArray<AActor*> params;
		//params.Add(this);
		//UGameplayStatics::Blueprint_PredictProjectilePath_ByTraceChannel(GetWorld(), hitInfo, pathPosition, lastTrace, compLeftCon->GetComponentLocation(),
		//	fireVelocity, false, 5.0f, ECC_WorldDynamic, false, params, EDrawDebugTrace::None, 1.0f, 15.0f, 1.0f, 0.0f);
		FPredictProjectilePathParams params;
		params.StartLocation = compLeftCon->GetComponentLocation();
		params.LaunchVelocity = fireVelocity;
		params.bTraceWithCollision = false;
		params.bTraceComplex = false;
		params.DrawDebugType = EDrawDebugTrace::None;
		params.DrawDebugTime = 1.0f;
		params.SimFrequency = 13.0f;
		params.OverrideGravityZ = 0.0f;
		params.TraceChannel = ECC_WorldDynamic; // Trace by channel
		FPredictProjectilePathResult PredictResult;
		bool bHit = UGameplayStatics::PredictProjectilePath(GetWorld(), params, PredictResult);
		PredictResult.PathData;
		for (const FPredictProjectilePathPointData& PathPoint : PredictResult.PathData) {
			FVector location = FVector(PathPoint.Location.X, PathPoint.Location.Y, PathPoint.Location.Z + 30);
			AActor* prediction = GetWorld()->SpawnActor<APredictionObject>(pathFactory, location, FRotator(0.0f));
			APredictionObject* path = Cast<APredictionObject>(prediction);
			path->mesh->SetCollisionProfileName(TEXT("NoCollision"));
		}
	}
}

// Called to bind functionality to input
void ARIM_Player::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//[Enhanced Action Events]
	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	if (EnhancedInputComponent != nullptr)
	{
		//�� ��ų�� ��� ---> ������ �׸� �ڡڡڽ��� ���ӿ����� ������ Ʈ���� ���
		EnhancedInputComponent->BindAction(rightGrip, ETriggerEvent::Started, this, &ARIM_Player::readyShoot);
		EnhancedInputComponent->BindAction(rightGrip, ETriggerEvent::Completed, this, &ARIM_Player::shootBird);
		//�߻� �Լ� ���� ---> ���� Ʈ���� �̸� ���� �ڵ� �߰� �ʿ�...?
		//���ϴ� �ڵ�
		EnhancedInputComponent->BindAction(leftX, ETriggerEvent::Started, this, &ARIM_Player::cancelShoot);


		//�׽�Ʈ ---> �Ķ��� ��ų
		//EnhancedInputComponent->BindAction(rightA, ETriggerEvent::Started, this, &ARIM_Player::BlueSkill);
		//�׽�Ʈ ---> ������ ��ų
		EnhancedInputComponent->BindAction(rightB, ETriggerEvent::Started, this, &ARIM_Player::InputSkill);
		//�̵� �Լ� ���� ---> ������ Ʈ����
		compMove->SetupPlayerInputComponent(EnhancedInputComponent);
		widgetComp->SetupPlayerInputComponent(EnhancedInputComponent); //RIM_WidgetPointerComponent
	}
}


//���� �ð� ���� �� ù��° �� ����
// void ARIM_Player::birdSetting()
// {
// 	//blueBird->meshBlue->SetVisibility(true);
// }

//��ų ���
void ARIM_Player::InputSkill()
{
	birdYellow = Cast<AKYI_AngryChuck>(UGameplayStatics::GetActorOfClass(GetWorld(), yellowFactory));
	birdBlack = Cast<ARIM_BirdBlack>(UGameplayStatics::GetActorOfClass(GetWorld(), blackFactory));
	birdBlue = Cast<ARIM_BirdBlue>(UGameplayStatics::GetActorOfClass(GetWorld(), blueFactory));
	if (birdYellow) {
		YellowSkill();
	}
	else if (birdBlue) {
		BlueSkill();
	}
	else if (birdBlack) {
		BlackSkill();
	}
}


//�Ķ��� ��ų
void ARIM_Player::BlueSkill() {
	FRotator actorRot;
	ARIM_BirdBlue* tempBlue;
	tempBlue = Cast<ARIM_BirdBlue>(UGameplayStatics::GetActorOfClass(GetWorld(), blueFactory));

	actorRot = tempBlue->GetActorRotation();
	actorRot.Yaw -= 30;
	ARIM_BirdBlue* secondBlue = GetWorld()->SpawnActor<ARIM_BirdBlue>(blueFactory, tempBlue->GetActorLocation(), actorRot);
	secondBlue->compCollision->AddImpulse(birdBlue->compCollision->GetPhysicsLinearVelocity(), FName("NAME_NONE"), true);

	actorRot = tempBlue->GetActorRotation();
	actorRot.Yaw += 60;
	ARIM_BirdBlue* thirdBlue = GetWorld()->SpawnActor<ARIM_BirdBlue>(blueFactory, tempBlue->GetActorLocation(), actorRot);
	thirdBlue->compCollision->AddImpulse(birdBlue->compCollision->GetPhysicsLinearVelocity(), FName("NAME_NONE"), true);
}

//����� ��ų
void ARIM_Player::YellowSkill() {
	birdYellow = Cast<AKYI_AngryChuck>(UGameplayStatics::GetActorOfClass(GetWorld(), yellowFactory));
	if (birdYellow) {
		FVector speed = birdYellow->sphereComp->GetPhysicsLinearVelocity();
		birdYellow->sphereComp->AddImpulse(speed * 5, FName("NAME_NONE"), true);
	}
}

//������ ��ų
void ARIM_Player::BlackSkill()
{
	AActor* tempActor = UGameplayStatics::GetActorOfClass(GetWorld(), blackFactory);
	birdBlack = Cast<ARIM_BirdBlack>(tempActor);
	if (birdBlack) {
		birdBlack->ExplosionDamage(); //�� ���� ������ ���� ����. �ı� �Ǵ� ���
		birdBlack->Destroy(); //���� ������. ��������
	}
}

void ARIM_Player::readyShoot() {
	bShouldPredict = true;
	bWillShoot = true;
	playSound(slingSound);
}

void ARIM_Player::shootBird() {
	if (!bWillShoot) {
		return;
	}
	bShouldPredict = false;
	FVector position = compLeftCon->GetComponentLocation();
	position.Z += 30;
	if (redCount > 0) {
		birdRed = GetWorld()->SpawnActor<AKYI_AngryRed>(redFactory, position, GetActorRotation());
		birdRed->sphereComp->AddImpulse(fireVelocity, FName("NAME_NONE"), true);
		playSound(redSound);
		redCount--;
	}
	else if (yellowCount > 0) {
		birdYellow = GetWorld()->SpawnActor<AKYI_AngryChuck>(yellowFactory, position, GetActorRotation());
		birdYellow->sphereComp->AddImpulse(fireVelocity, FName("NAME_NONE"), true);
		playSound(yellowSound);
		yellowCount--;
	}
	else if (blueCount > 0) {
		birdBlue = GetWorld()->SpawnActor<ARIM_BirdBlue>(blueFactory, position, GetActorRotation());
		birdBlue->compCollision->AddImpulse(fireVelocity, FName("NAME_NONE"), true);
		playSound(blueSound);
		blueCount--;
	}
	else if (blackCount > 0) {
		birdBlack = GetWorld()->SpawnActor<ARIM_BirdBlack>(blackFactory, position, GetActorRotation());
		birdBlack->compCollision->AddImpulse(fireVelocity, FName("NAME_NONE"), true);
		blackCount--;
	}
}

void ARIM_Player::playSound(class USoundBase* sound) {
	UGameplayStatics::PlaySound2D(GetWorld(), sound, 5);
}


void ARIM_Player::cancelShoot() {
	bWillShoot = false;
	bShouldPredict = false;
}

