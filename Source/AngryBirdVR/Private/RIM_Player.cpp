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
#include <../Plugins/EnhancedInput/Source/EnhancedInput/Public/InputActionValue.h>
#include "RIM_Pig.h"
#include "RIM_WidgetInGameScoreActor.h"
#include "RIM_WidgetInGameFailActor.h"

// Sets default values
ARIM_Player::ARIM_Player()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//[ī�޶�]
	//ī�޶�
	compCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera")); //�÷��̾ ������Ʈ �߰�. CameraComponent ��Ŭ���
	compCamera->SetupAttachment(RootComponent); //��Ʈ������Ʈ �ڽ����� ����
	compCamera->SetRelativeLocation(FVector(-20, 0, 0)); //���ʿ� �� ���� ����

	//[�޼�]
	//��Ʈ�ѷ�
	compLeftCon = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("LeftController")); //�÷��̾ ������Ʈ �߰�
	compLeftCon->SetupAttachment(RootComponent); //��Ʈ������Ʈ �ڽ����� ����
	compWidgetPointer_left = CreateDefaultSubobject<UWidgetInteractionComponent>(TEXT("Left Widget Pointer"));
	compWidgetPointer_left->SetupAttachment(compLeftCon);

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
	logLeft->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f)); //�ؽ�Ʈ 180 ����
	logLeft->SetTextRenderColor(FColor::Yellow);
	logLeft->SetHorizontalAlignment(EHTA_Right);
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
	meshRightHand->SetRelativeRotation(FRotator(25.0f, 0.0f, 90.0f)); //���ʿ� �� ���� ����
	//�α�(Ȯ�ο�)
	//logRight = CreateDefaultSubobject<UTextRenderComponent>(TEXT("RightLogText"));
	//logRight->SetupAttachment(compRightCon);
	//logRight->SetRelativeRotation(FRotator(0.0f, 180.0f, 0.0f)); //�ؽ�Ʈ 180 ����
	//logRight->SetTextRenderColor(FColor::Yellow);
	//logRight->SetHorizontalAlignment(EHTA_Center);
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
	//�̵�, �ڷ���Ʈ ����
	compMove = CreateDefaultSubobject<URIM_MoveComponent>(TEXT("MoveComponent"));
	//���� ����
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
	ConstructorHelpers::FObjectFinder<USoundBase> tempExploSound(TEXT("/Script/Engine.SoundWave'/Game/Resource/Sound/TNTExplosionSound.TNTExplosionSound'"));
	if (tempExploSound.Succeeded()) {
		exploSound = tempExploSound.Object;
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
	logLeft->SetVisibility(false);
}

// Called every frame
void ARIM_Player::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (bShouldPredict) {
		rightHandPosition = compRightCon->GetComponentLocation();
		fireVelocity = (compLeftCon->GetComponentLocation() - rightHandPosition) * 50;
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
		for (const FPredictProjectilePathPointData& PathPoint : PredictResult.PathData) {
			FVector location = FVector(PathPoint.Location.X, PathPoint.Location.Y, PathPoint.Location.Z + 30);
			AActor* prediction = GetWorld()->SpawnActor<APredictionObject>(pathFactory, location, FRotator(0.0f));
			APredictionObject* path = Cast<APredictionObject>(prediction);
			path->mesh->SetCollisionProfileName(TEXT("NoCollision"));
		}
	}
	//���� �������ִ� ���� ������ ����Ѵ�
	birdCalc();
	//���緹���� ���� ������ ����׶����� ��Ȱ��ȭ�Ѵ�
	FString name = UGameplayStatics::GetCurrentLevelName(GetWorld());
	if (name.Contains("Stage1_")) {
		compWidgetPointer_right->bShowDebug = false;
	}
	//���࿡ ���� ȭ�鿡 ����ȭ���� �ִٸ� ������ ������ ������ �����ϱ� ���� �Ѵ�
	TArray<AActor*> tempArray;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ARIM_WidgetInGameScoreActor::StaticClass(), tempArray);
	float gameNum = tempArray.Num();
	tempArray.Empty();
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ARIM_WidgetInGameFailActor::StaticClass(), tempArray);
	float failNum = tempArray.Num();
	UE_LOG(LogTemp, Warning, TEXT("%d, %d"), gameNum, failNum);
	if (gameNum > 0 || failNum > 0) {
		compWidgetPointer_right->bShowDebug = true;
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
		EnhancedInputComponent->BindAction(rightGrip, ETriggerEvent::Started, this, &ARIM_Player::readyShoot); // ---> ���ϴ� �߰�
		EnhancedInputComponent->BindAction(rightGrip, ETriggerEvent::Ongoing, this, &ARIM_Player::rightConHaptic);
		EnhancedInputComponent->BindAction(rightGrip, ETriggerEvent::Completed, this, &ARIM_Player::shootBird); // ---> ���ϴ� �߰�

		EnhancedInputComponent->BindAction(rightA, ETriggerEvent::Started, this, &ARIM_Player::Reset); // ---> ���ϴ� �߰�
		EnhancedInputComponent->BindAction(leftY, ETriggerEvent::Started, this, &ARIM_Player::showCount);
		EnhancedInputComponent->BindAction(leftY, ETriggerEvent::Completed, this, &ARIM_Player::hideCount);
		EnhancedInputComponent->BindAction(leftX, ETriggerEvent::Started, this, &ARIM_Player::cancelShoot);
		//�׽�Ʈ ---> �Ķ��� ��ų
		//EnhancedInputComponent->BindAction(rightA, ETriggerEvent::Started, this, &ARIM_Player::BlueSkill); // ---> ���ϴ� ����
		//�׽�Ʈ ---> ������ ��ų
		//EnhancedInputComponent->BindAction(rightB, ETriggerEvent::Started, this, &ARIM_Player::BlackSkill); // ---> ���ϴ� ����
		EnhancedInputComponent->BindAction(rightB, ETriggerEvent::Started, this, &ARIM_Player::InputSkill); // ---> ���ϴ� ����. ���� �ڵ带 ����
		EnhancedInputComponent->BindAction(rightThumbstick, ETriggerEvent::Triggered, this, &ARIM_Player::RotateAxis);

		//�̵� �Լ� ���� ---> ������ Ʈ����
		compMove->SetupPlayerInputComponent(EnhancedInputComponent);

		//���� ������ ��� ---> ������/�޼� Ʈ����
		//compWidgetPointer_right->SetupPlayerInputComponent(EnhancedInputComponent); // ----> �̰� �ƴ�
		//compWidgetPointer_left->SetupPlayerInputComponent(EnhancedInputComponent); // ----> �̰� �ƴ�
		widgetComp->SetupPlayerInputComponent(EnhancedInputComponent); //RIM_WidgetPointerComponent ������Ʈ. �����Ͱ� �۵��ϱ� ���� �ʿ� ---> ���ϴ� �߰�


	}
}

void ARIM_Player::RotateAxis(const FInputActionValue& value)
{
	FVector2D axis = value.Get<FVector2D>();

	// axis ���� �̿��ؼ� ĳ����(��Ʈ�ѷ�)�� ȸ���Ѵ�.
	AddControllerPitchInput(axis.Y * -1.0f);
	AddControllerYawInput(axis.X);
}

//��ų ��� ---> ���ϴ� ��ü ����
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


//�Ķ��� ��ų ---> ���ϴ� ����
void ARIM_Player::BlueSkill() {
	FRotator actorRot;
	ARIM_BirdBlue* tempBlue;
	tempBlue = Cast<ARIM_BirdBlue>(UGameplayStatics::GetActorOfClass(GetWorld(), blueFactory));

	actorRot = tempBlue->GetActorRotation();
	actorRot.Yaw = actorRot.Yaw - 30.0;
	ARIM_BirdBlue* secondBlue = GetWorld()->SpawnActor<ARIM_BirdBlue>(blueFactory, tempBlue->GetActorLocation(), actorRot);
	secondBlue->compCollision->AddImpulse(birdBlue->compCollision->GetPhysicsLinearVelocity(), FName("NAME_NONE"), true);

	actorRot = tempBlue->GetActorRotation();
	actorRot.Yaw = actorRot.Yaw + 60.0;
	ARIM_BirdBlue* thirdBlue = GetWorld()->SpawnActor<ARIM_BirdBlue>(blueFactory, tempBlue->GetActorLocation(), actorRot);
	thirdBlue->compCollision->AddImpulse(birdBlue->compCollision->GetPhysicsLinearVelocity(), FName("NAME_NONE"), true);
}

//����� ��ų ---> ���ϴ� �߰�
void ARIM_Player::YellowSkill() {
	birdYellow = Cast<AKYI_AngryChuck>(UGameplayStatics::GetActorOfClass(GetWorld(), yellowFactory));
	if (birdYellow) {
		FVector speed = birdYellow->sphereComp->GetPhysicsLinearVelocity();
		birdYellow->sphereComp->AddImpulse(speed * 2, FName("NAME_NONE"), true);
	}
}

//������ ��ų 
void ARIM_Player::BlackSkill()
{
	AActor* tempActor = UGameplayStatics::GetActorOfClass(GetWorld(), blackFactory); //---> ���ϴ� �߰�
	birdBlack = Cast<ARIM_BirdBlack>(tempActor); //---> ���ϴ� �߰�
	
	// �Ʒ� �ڵ� �� if ���� ���ϴ� �߰�
	if (birdBlack) { 
		birdBlack->ExplosionDamage(); //�� ���� ������ ���� ����. �ı� �Ǵ� ���
		playSound(exploSound);
		birdBlack->Destroy(); //���� ������. ��������
	}
}

//�Ʒ� �ڵ� ���ϴ� �߰�
void ARIM_Player::readyShoot() {
	bShouldPredict = true;
	bWillShoot = true;
	playSound(slingSound);
}

void ARIM_Player::cancelShoot() {
	bWillShoot = false;
	bShouldPredict = false;
}

//�Ʒ� �ڵ� ���ϴ� �߰�
void ARIM_Player::shootBird() {
	if (!bWillShoot) {
		return;
	}
	bShouldPredict = false;
	FVector position = compLeftCon->GetComponentLocation();
	position.Z = position.Z + 30.0;
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

void ARIM_Player::rightConHaptic() {
	GetWorld()->GetFirstPlayerController()->PlayHapticEffect(grabHaptic, EControllerHand::Right, 1, false);
	GetWorld()->GetFirstPlayerController()->PlayHapticEffect(grabHaptic, EControllerHand::Left, 1, false);
}

void ARIM_Player::birdCalc() {
	FString count = FString::Printf(TEXT("Bird Count: %d\nRed: %d\nYellow: %d\nBlue: %d\nBlack: %d"), birdCount, redCount, yellowCount, blueCount, blackCount);
	logLeft->SetText(FText::FromString(count));
	birdCount = redCount + yellowCount + blueCount + blackCount;
}

void ARIM_Player::Reset() {
	redCount = 1;
	yellowCount = 1;
	blueCount = 1;
	blackCount = 1;
}

void ARIM_Player::showCount() {
	logLeft->SetVisibility(true);
}

void ARIM_Player::hideCount() {
	logLeft->SetVisibility(false);
}

