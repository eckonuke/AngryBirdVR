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

// Sets default values
ARIM_Player::ARIM_Player()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//[플레이어]
	//GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision); //본체 충돌 컴포넌트. 노콜리전. CapsuleComponent 인클루드 ★★★확인 필요. 필요 없을 거 같은데 혹시 몰라서 작성

	//[카메라]
	//카메라
	compCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera")); //플레이어에 컴포넌트 추가. CameraComponent 인클루드
	compCamera->SetupAttachment(RootComponent); //루트컴포넌트 자식으로 세팅
	compCamera->SetRelativeLocation(FVector(-20, 0, 0)); //▶필요 시 추후 변경
	//메시
// 	ConstructorHelpers::FObjectFinder<UStaticMesh> tempCamera(TEXT("/Script/Engine.StaticMesh'/Engine/EditorMeshes/MatineeCam_SM.MatineeCam_SM'"));
// 	if (tempCamera.Succeeded())
// 	{
// 		meshCamera->SetStaticMesh(tempCamera.Object);
// 	}
// 	meshCamera->SetCollisionEnabled(ECollisionEnabled::NoCollision); //메시 노콜리전

	//[왼손]
	//컨트롤러
	compLeftCon = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("LeftController")); //플레이어에 컴포넌트 추가
	compLeftCon->SetupAttachment(RootComponent); //루트컴포넌트 자식으로 세팅
 	//메시(스켈레탈)
 	meshLeftHand = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SlingShot")); //플레이어에 메시 컴포넌트 추가. SkeletalMeshComponent 인클루드
 	meshLeftHand->SetupAttachment(compLeftCon); //왼손 컨트롤러 자식으로 세팅
 	ConstructorHelpers::FObjectFinder<USkeletalMesh> tempLeftHand(TEXT("/Script/Engine.SkeletalMesh'/Game/Characters/MannequinsXR/Meshes/SKM_MannyXR_left.SKM_MannyXR_left'")); //▶엔진 기본 에셋 사용. 추후 변경
 	if (tempLeftHand.Succeeded())
 	{
 		meshLeftHand->SetSkeletalMesh(tempLeftHand.Object);
 	}
 	meshLeftHand->SetCollisionEnabled(ECollisionEnabled::NoCollision); //메시 노콜리전
 	meshLeftHand->SetRelativeLocation(FVector(0, -20, 0)); //▶필요 시 추후 변경 
 	meshLeftHand->SetRelativeRotation(FRotator(-25.0f, 180.0f, 90.0f)); //▶필요 시 추후 변경 

	//메시(테스트총)
// 	meshLeftHand = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SlingShot")); //플레이어에 메시 컴포넌트 추가. SkeletalMeshComponent 인클루드
// 	meshLeftHand->SetupAttachment(compLeftCon); //왼손 컨트롤러 자식으로 세팅
// 	ConstructorHelpers::FObjectFinder<USkeletalMesh> tempLeftHand(TEXT("/Script/Engine.SkeletalMesh'/Game/FPWeapon/Mesh/SK_FPGun.SK_FPGun'")); //▶엔진 기본 에셋 사용. 추후 변경
// 	if (tempLeftHand.Succeeded())
// 	{
// 		meshLeftHand->SetSkeletalMesh(tempLeftHand.Object);
// 	}
// 	meshLeftHand->SetCollisionEnabled(ECollisionEnabled::NoCollision); //메시 노콜리전
// 	meshLeftHand->SetRelativeLocation(FVector(0, -20, 0)); //▶필요 시 추후 변경 
// 	meshLeftHand->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f)); //▶필요 시 추후 변경 
// 	meshLeftHand->SetRelativeScale3D(FVector(0.5f)); //▶필요 시 추후 변경 
	
 	//메시(스테틱)
	//meshLeftHand = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LeftHand")); //플레이어에 메시 컴포넌트 추가. StaticMeshComponent 인클루드
	//meshLeftHand->SetupAttachment(compLeftCon); //왼손 컨트롤러 자식으로 세팅
	//ConstructorHelpers::FObjectFinder<UStaticMesh> tempLeftHand(TEXT("/Script/Engine.StaticMesh'/Game/Resource/Test_SlingShot/SlingShot_01/Source/Slingshot2.Slingshot2'")); //▶추후 변경
	//if (tempLeftHand.Succeeded())
	//{
	//	meshLeftHand->SetStaticMesh(tempLeftHand.Object);
	//}
	//meshLeftHand->SetCollisionEnabled(ECollisionEnabled::NoCollision); //메시 노콜리전
	//meshLeftHand->SetRelativeLocation(FVector(20, 0, -15)); //▶필요 시 추후 변경
	//meshLeftHand->SetRelativeRotation(FRotator(0.0f, 90.0f, -30.0f)); //▶필요 시 추후 변경
	//meshLeftHand->SetRelativeScale3D(FVector(0.18f)); //▶필요 시 추후 변경
	//로그(확인용)
	logLeft = CreateDefaultSubobject<UTextRenderComponent>(TEXT("LeftLogText"));
	logLeft->SetupAttachment(compLeftCon);
	logLeft->SetRelativeRotation(FRotator(0.0f, 180.0f, 0.0f)); //텍스트 180 수정
	logLeft->SetTextRenderColor(FColor::Yellow);
	logLeft->SetHorizontalAlignment(EHTA_Center);
	//logLeft >SetVerticalAlignment(EVRTA_TextCenter);
	//모션 소스 선택
	compLeftCon->MotionSource = "Left"; //★★★???

	//[오른손]
	//컨트롤러
	compRightCon = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("RightController")); //플레이어에 컴포넌트 추가. MotionControllerComponent 인클루드
	compRightCon->SetupAttachment(RootComponent); //루트컴포넌트 자식으로 세팅
	//메시
	meshRightHand = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("RightHand")); //플레이어에 메시 컴포넌트 추가. SkeletalMeshComponent 인클루드. ▶추후변경(현재 스켈레탈메시)
	meshRightHand->SetupAttachment(compRightCon); //오른손 컨트롤러 자식으로 세팅
	ConstructorHelpers::FObjectFinder<USkeletalMesh> tempRihgtHand(TEXT("/Script/Engine.SkeletalMesh'/Game/Characters/MannequinsXR/Meshes/SKM_MannyXR_right.SKM_MannyXR_right'")); //▶추후변경(현재 스켈레탈메시)
	if (tempRihgtHand.Succeeded())
	{
		meshRightHand->SetSkeletalMesh(tempRihgtHand.Object);
	}
	meshRightHand->SetCollisionEnabled(ECollisionEnabled::NoCollision); //메시 노콜리전
	//meshLeftHand->SetRelativeLocation(FVector(0, 20, 0)); //▶필요 시 추후 변경
	meshRightHand->SetRelativeRotation(FRotator(25.0f, 0.0f, 90.0f)); //▶필요 시 추후 변경
	//로그(확인용)
	logRight = CreateDefaultSubobject<UTextRenderComponent>(TEXT("RightLogText"));
	logRight->SetupAttachment(compRightCon);
	logRight->SetRelativeRotation(FRotator(0.0f, 180.0f, 0.0f)); //텍스트 180 수정
	logRight->SetTextRenderColor(FColor::Yellow);
	logRight->SetHorizontalAlignment(EHTA_Center);
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
	//MoveComponent 추가
	compMove = CreateDefaultSubobject<URIM_MoveComponent>(TEXT("MoveComponent"));

	//발사Component 추가
	//용일님 코드


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


	
	//일정 시간 지난 후 첫번째 새 노출
// 	FTimerHandle settingTimer;
// 	GetWorld()->GetTimerManager().SetTimer(settingTimer, this, &ARIM_Player::birdSetting, delaySettingTime, false); //타이머

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
		//새 스킬들 사용 ---> 오른손 그립 ★★★실제 게임에서는 오른손 트리거 사용
		EnhancedInputComponent->BindAction(rightGrip, ETriggerEvent::Started, this, &ARIM_Player::InputSkill);

		//이동 함수 실행 ---> 오른손 트리거
		compMove->SetupPlayerInputComponent(EnhancedInputComponent);
		
		//발사 함수 실행 ---> 만약 트리거 이면 조건 코드 추가 필요...?
		//용일님 코드



		//테스트 ---> 파란새 스킬
		EnhancedInputComponent->BindAction(rightA, ETriggerEvent::Started, this, &ARIM_Player::BlueSkill);
		//테스트 ---> 검은새 스킬
		EnhancedInputComponent->BindAction(rightB, ETriggerEvent::Started, this, &ARIM_Player::BlackSkill);



	}




}


	//일정 시간 지난 후 첫번째 새 노출
// void ARIM_Player::birdSetting()
// {
// 	//blueBird->meshBlue->SetVisibility(true);
// }

//스킬 사용
void ARIM_Player::InputSkill()
{
// 	FString msg = FString(__FUNCTION__); //확인용 로그
// 	logRight->SetText(FText::FromString(msg)); //확인용 로그
// 
// 	FRotator actorRot;
// 
// 	GetWorld()->SpawnActor<ARIM_BirdBlue>(blueFactory, GetActorLocation() + GetActorForwardVector() * 200, GetActorRotation());
// 	
// 	actorRot = GetActorRotation();
// 	actorRot.Yaw -= 30;
// 	GetWorld()->SpawnActor<ARIM_BirdBlue>(blueFactory, GetActorLocation() + GetActorForwardVector() * 200, actorRot);
// 	
// 	actorRot = GetActorRotation();
// 	actorRot.Yaw += 30;
// 	GetWorld()->SpawnActor<ARIM_BirdBlue>(blueFactory, GetActorLocation() + GetActorForwardVector() * 200, actorRot);

// 	if () //노란새 스킬 사용 조건
// 	{
// 		UE_LOG(LogTemp, Warning, TEXT("Yellow Skill -----> Fire !!!!!!!!!!"));
// 
// 	
// 
// 	}
// 	else if () //파란새 스킬 사용 조건
// 	{
// 		UE_LOG(LogTemp, Warning, TEXT("Blue Skill -----> Fire !!!!!!!!!!"));
// 
// 		BlueSkill();
// 		//★★★ 한 번 스킬 사용하고 사용 못하게 하는 코드 추가 필요
// 
// 	}
// 	else if () //검은새 스킬 사용 조건
// 	{
// 		UE_LOG(LogTemp, Warning, TEXT("Black Skill -----> Fire !!!!!!!!!!"));
// 
// 		BlackSkill();
// 		//★★★ 한 번 스킬 사용하고 사용 못하게 하는 코드 추가 필요
// 
// 	}

	
}


//파란새 스킬
void ARIM_Player::BlueSkill()
{
	UE_LOG(LogTemp, Warning, TEXT("Blue Skill !!!!!!!!!!"));

	FRotator actorRot;

	birdBlue = GetWorld()->SpawnActor<ARIM_BirdBlue>(blueFactory, compLeftCon->GetComponentLocation() + GetActorForwardVector() * 200, GetActorRotation());

	actorRot = birdBlue->GetActorRotation();
	actorRot.Yaw -= 30;
	GetWorld()->SpawnActor<ARIM_BirdBlue>(blueFactory, birdBlue->GetActorLocation() + birdBlue->GetActorForwardVector() * 200, actorRot);

	actorRot = birdBlue->GetActorRotation();
	actorRot.Yaw += 30;
	GetWorld()->SpawnActor<ARIM_BirdBlue>(blueFactory, birdBlue->GetActorLocation() + birdBlue->GetActorForwardVector() * 200, actorRot);
}


//검은새 스킬
void ARIM_Player::BlackSkill()
{
	UE_LOG(LogTemp, Warning, TEXT("Black Skill !!!!!!!!!!"));
	if (birdBlack != nullptr) {
		birdBlack->ExplosionDamage(); //새 폭발 범위에 따른 피해. 파괴 또는 충격
		birdBlack->Destroy(); //새가 터진다. 없어진다
	}
}


void ARIM_Player::PredictionPath() {
	
}