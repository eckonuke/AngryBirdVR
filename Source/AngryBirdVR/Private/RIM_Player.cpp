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

	//[카메라]
	//카메라
	compCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera")); //플레이어에 컴포넌트 추가. CameraComponent 인클루드
	compCamera->SetupAttachment(RootComponent); //루트컴포넌트 자식으로 세팅
	compCamera->SetRelativeLocation(FVector(-20, 0, 0)); //▶필요 시 추후 변경

	//[왼손]
	//컨트롤러
	compLeftCon = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("LeftController")); //플레이어에 컴포넌트 추가
	compLeftCon->SetupAttachment(RootComponent); //루트컴포넌트 자식으로 세팅
	compWidgetPointer_left = CreateDefaultSubobject<UWidgetInteractionComponent>(TEXT("Left Widget Pointer"));
	compWidgetPointer_left->SetupAttachment(compLeftCon);

	//메시(스테틱)
	meshLeftHand = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LeftHand")); //플레이어에 메시 컴포넌트 추가. StaticMeshComponent 인클루드
	meshLeftHand->SetupAttachment(compLeftCon); //왼손 컨트롤러 자식으로 세팅
	ConstructorHelpers::FObjectFinder<UStaticMesh> tempLeftHand(TEXT("/Script/Engine.StaticMesh'/Game/Resource/Test_SlingShot/SlingShot_01/Source/Slingshot2.Slingshot2'")); //▶추후 변경
	if (tempLeftHand.Succeeded())
	{
		meshLeftHand->SetStaticMesh(tempLeftHand.Object);
	}
	meshLeftHand->SetCollisionEnabled(ECollisionEnabled::NoCollision); //메시 노콜리전
	meshLeftHand->SetRelativeLocation(FVector(0)); //▶필요 시 추후 변경
	meshLeftHand->SetRelativeRotation(FRotator(0.0f, 90.0f, -90.0f)); //▶필요 시 추후 변경
	meshLeftHand->SetRelativeScale3D(FVector(0.3f)); //▶필요 시 추후 변경
	//로그(확인용)
	logLeft = CreateDefaultSubobject<UTextRenderComponent>(TEXT("LeftLogText"));
	logLeft->SetupAttachment(compLeftCon);
	logLeft->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f)); //텍스트 180 수정
	logLeft->SetTextRenderColor(FColor::Yellow);
	logLeft->SetHorizontalAlignment(EHTA_Right);
	//모션 소스 선택
	compLeftCon->MotionSource = "Left"; //★★★???

	//[오른손]
	//컨트롤러
	compRightCon = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("RightController")); //플레이어에 컴포넌트 추가. MotionControllerComponent 인클루드
	compRightCon->SetupAttachment(RootComponent); //루트컴포넌트 자식으로 세팅
	compWidgetPointer_right = CreateDefaultSubobject<UWidgetInteractionComponent>(TEXT("Right Widget Pointer"));
	compWidgetPointer_right->SetupAttachment(compRightCon);
	//메시
	meshRightHand = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("RightHand")); //플레이어에 메시 컴포넌트 추가. SkeletalMeshComponent 인클루드. ▶추후변경(현재 스켈레탈메시)
	meshRightHand->SetupAttachment(compRightCon); //오른손 컨트롤러 자식으로 세팅
	ConstructorHelpers::FObjectFinder<USkeletalMesh> tempRihgtHand(TEXT("/Script/Engine.SkeletalMesh'/Game/Characters/MannequinsXR/Meshes/SKM_MannyXR_right.SKM_MannyXR_right'")); //▶추후변경(현재 스켈레탈메시)
	if (tempRihgtHand.Succeeded())
	{
		meshRightHand->SetSkeletalMesh(tempRihgtHand.Object);
	}
	meshRightHand->SetCollisionEnabled(ECollisionEnabled::NoCollision); //메시 노콜리전
	meshRightHand->SetRelativeRotation(FRotator(25.0f, 0.0f, 90.0f)); //▶필요 시 추후 변경
	//로그(확인용)
	//logRight = CreateDefaultSubobject<UTextRenderComponent>(TEXT("RightLogText"));
	//logRight->SetupAttachment(compRightCon);
	//logRight->SetRelativeRotation(FRotator(0.0f, 180.0f, 0.0f)); //텍스트 180 수정
	//logRight->SetTextRenderColor(FColor::Yellow);
	//logRight->SetHorizontalAlignment(EHTA_Center);
	//logRight > SetVerticalAlignment(EVRTA_TextCenter);
	//모션 소스 선택
	compRightCon->MotionSource = "Right"; //★★★???

	//[컨트롤러]
	//axis 값을 이용해서 캐릭터(컨트롤러)를 회전한다
	bUseControllerRotationPitch = true; //★★★???

	//★★★???
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	//파란새 클래스 가져와서 등록. 내가 원하는 때에 스폰하려고 파란새를 변수에 담아 놓음...? ★★★우선 파란새로 진행 ---> 테스트
	ConstructorHelpers::FClassFinder<ARIM_BirdBlue> tempBlue(TEXT("/Script/Engine.Blueprint'/Game/BluePrints/BP_AngryBlue.BP_AngryBlue_C'")); // 블루프린트 경로. _C'
	if (tempBlue.Succeeded())
	{
		blueFactory = tempBlue.Class;
	}

	//검은새 클래스 가져와서 등록
	//ConstructorHelpers::FClassFinder<ARIM_BirdBlue> tempBlack(TEXT("/Script/Engine.Blueprint'/Game/BluePrints/BP_AngryBlack.BP_AngryBlack_C'")); // 블루프린트 경로. _C'
	//if (tempBlack.Succeeded())
	//{
	//	blackFactory = tempBlack.Class;
	//}

	//[플레이어에 액터 컴포넌트 추가]
	//이동, 텔레포트 관련
	compMove = CreateDefaultSubobject<URIM_MoveComponent>(TEXT("MoveComponent"));
	//위젯 관련
	widgetComp = CreateDefaultSubobject<URIM_WidgetPointerComponent>(TEXT("Widget Component"));

	//발사Component 추가
	//용일님 코드
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

	//1. 플레이어 컨트롤러를 가져온다.
	APlayerController* playerCon = GetWorld()->GetFirstPlayerController();

	//2. 플레이어 컨트롤러에서 EnhancedInputLocalPlayerSubsystem 을 가져온다.
	UEnhancedInputLocalPlayerSubsystem* subsys = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(playerCon->GetLocalPlayer());

	//3. 가져온 Subsystem 에 IMC 를 등록한다.(우선순위 0번)
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
	//현재 가지고있는 새의 갯수를 계산한다
	birdCalc();
	//현재레벨을 보고 포인터 디버그라인을 비활성화한다
	FString name = UGameplayStatics::GetCurrentLevelName(GetWorld());
	if (name.Contains("Stage1_")) {
		compWidgetPointer_right->bShowDebug = false;
	}
	//만약에 지금 화면에 점수화면이 있다면 포인터 라인을 보여서 선택하기 쉽게 한다
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
		//새 스킬들 사용 ---> 오른손 그립 ★★★실제 게임에서는 오른손 트리거 사용
		EnhancedInputComponent->BindAction(rightGrip, ETriggerEvent::Started, this, &ARIM_Player::readyShoot); // ---> 용일님 추가
		EnhancedInputComponent->BindAction(rightGrip, ETriggerEvent::Ongoing, this, &ARIM_Player::rightConHaptic);
		EnhancedInputComponent->BindAction(rightGrip, ETriggerEvent::Completed, this, &ARIM_Player::shootBird); // ---> 용일님 추가

		EnhancedInputComponent->BindAction(rightA, ETriggerEvent::Started, this, &ARIM_Player::Reset); // ---> 용일님 추가
		EnhancedInputComponent->BindAction(leftY, ETriggerEvent::Started, this, &ARIM_Player::showCount);
		EnhancedInputComponent->BindAction(leftY, ETriggerEvent::Completed, this, &ARIM_Player::hideCount);
		EnhancedInputComponent->BindAction(leftX, ETriggerEvent::Started, this, &ARIM_Player::cancelShoot);
		//테스트 ---> 파란새 스킬
		//EnhancedInputComponent->BindAction(rightA, ETriggerEvent::Started, this, &ARIM_Player::BlueSkill); // ---> 용일님 수정
		//테스트 ---> 검은새 스킬
		//EnhancedInputComponent->BindAction(rightB, ETriggerEvent::Started, this, &ARIM_Player::BlackSkill); // ---> 용일님 수정
		EnhancedInputComponent->BindAction(rightB, ETriggerEvent::Started, this, &ARIM_Player::InputSkill); // ---> 용일님 수정. 위에 코드를 수정
		EnhancedInputComponent->BindAction(rightThumbstick, ETriggerEvent::Triggered, this, &ARIM_Player::RotateAxis);

		//이동 함수 실행 ---> 오른손 트리거
		compMove->SetupPlayerInputComponent(EnhancedInputComponent);

		//위젯 포인터 사용 ---> 오른손/왼손 트리거
		//compWidgetPointer_right->SetupPlayerInputComponent(EnhancedInputComponent); // ----> 이거 아님
		//compWidgetPointer_left->SetupPlayerInputComponent(EnhancedInputComponent); // ----> 이거 아님
		widgetComp->SetupPlayerInputComponent(EnhancedInputComponent); //RIM_WidgetPointerComponent 컴포넌트. 포인터가 작동하기 위해 필요 ---> 용일님 추가


	}
}

void ARIM_Player::RotateAxis(const FInputActionValue& value)
{
	FVector2D axis = value.Get<FVector2D>();

	// axis 값을 이용해서 캐릭터(콘트롤러)를 회전한다.
	AddControllerPitchInput(axis.Y * -1.0f);
	AddControllerYawInput(axis.X);
}

//스킬 사용 ---> 용일님 전체 수정
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


//파란새 스킬 ---> 용일님 수정
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

//노란새 스킬 ---> 용일님 추가
void ARIM_Player::YellowSkill() {
	birdYellow = Cast<AKYI_AngryChuck>(UGameplayStatics::GetActorOfClass(GetWorld(), yellowFactory));
	if (birdYellow) {
		FVector speed = birdYellow->sphereComp->GetPhysicsLinearVelocity();
		birdYellow->sphereComp->AddImpulse(speed * 2, FName("NAME_NONE"), true);
	}
}

//검은새 스킬 
void ARIM_Player::BlackSkill()
{
	AActor* tempActor = UGameplayStatics::GetActorOfClass(GetWorld(), blackFactory); //---> 용일님 추가
	birdBlack = Cast<ARIM_BirdBlack>(tempActor); //---> 용일님 추가
	
	// 아래 코드 중 if 조건 용일님 추가
	if (birdBlack) { 
		birdBlack->ExplosionDamage(); //새 폭발 범위에 따른 피해. 파괴 또는 충격
		playSound(exploSound);
		birdBlack->Destroy(); //새가 터진다. 없어진다
	}
}

//아래 코드 용일님 추가
void ARIM_Player::readyShoot() {
	bShouldPredict = true;
	bWillShoot = true;
	playSound(slingSound);
}

void ARIM_Player::cancelShoot() {
	bWillShoot = false;
	bShouldPredict = false;
}

//아래 코드 용일님 추가
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

