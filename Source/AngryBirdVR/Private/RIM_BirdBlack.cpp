// Fill out your copyright notice in the Description page of Project Settings.


#include "RIM_BirdBlack.h"
#include <Components/SphereComponent.h>
#include <Components/StaticMeshComponent.h>
#include <GameFramework/ProjectileMovementComponent.h>
#include "DrawDebugHelpers.h"
#include "KYI_AngryRed.h"
#include "KYI_AngryChuck.h"
#include "RIM_BirdBlue.h"
#include "RIM_BirdBlack.h"
#include "KYI_Wood.h"
#include "KYI_Glass.h"
#include "RIM_Pig.h"

// Sets default values
ARIM_BirdBlack::ARIM_BirdBlack()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//충돌체
	compCollision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	RootComponent = compCollision; //루트컴포넌트로 세팅. compCollision->SetupAttachment(RootComponent);
	compCollision->SetCollisionProfileName(TEXT("BlockAll"));
	compCollision->SetSphereRadius(10); //▶충돌체 크기. 추후 수정
	compCollision->SetSimulatePhysics(true);

	//외관
	meshBlack = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BlackBird"));
	meshBlack->SetupAttachment(compCollision);
	ConstructorHelpers::FObjectFinder<UStaticMesh> tempBird(TEXT("/Script/Engine.StaticMesh'/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere'")); //▶추후 수정
	if (tempBird.Succeeded())
	{
		meshBlack->SetStaticMesh(tempBird.Object);
	}
	meshBlack->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	//meshBlue->SetRelativeLocation(FVector(0, 0, 0)); //▶추후 수정
	meshBlack->SetRelativeScale3D(FVector(0.08f)); //▶추후 수정

	//발사체 ★★★영상에 의하면 필요없으나 일단 넣음
	compMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movement"));
	compMovement->SetUpdatedComponent(compCollision);
	compMovement->InitialSpeed = 0; //초기속도. ▶필요시 추후 수정
	compMovement->MaxSpeed = 0; //최대속도. ▶필요시 추후 수정
	compMovement->bShouldBounce = true; //반동여부. 튕기는 여부
	compMovement->Bounciness = 0.5f; //얼마나 잘 튕기에 할 것인가. 반동. 탄성. ▶필요시 추후 수정
	//InitialLifeSpan = 10.0f; //생명 시간. ▶필요시 추후 수정
}

// Called when the game starts or when spawned
void ARIM_BirdBlack::BeginPlay()
{
	Super::BeginPlay();
	
	//일정 시간 지난 후 새 파괴
	//FTimerHandle deathTimer;
	//GetWorld()->GetTimerManager().SetTimer(deathTimer, this, &ARIM_BirdBlue::Death, delayDeathTime, false); //타이머
}

// Called every frame
void ARIM_BirdBlack::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//앞방향으로 계속 이동 ★★★영상에 의하면 필요없으나 일단 넣음
	//P = P0 + vt
	//FVector p0 = GetActorLocation();
	//FVector vt = GetActorLocation() * 2000 * DeltaTime;

}

//일정 시간 지난 후 새 파괴
//void ARIM_BirdBlack::Death()
//{
//	Destroy();
//}


//[새가 터지면 발생하는 일]
//1. blastRange(폭탄 범위) 에서 폭탄에 일정 거리 이하로 위치해 있을 때, 적, 나무, 유리 파괴된다.
//2. blastRange(폭탄 범위) 에서 폭탄에 일정 거리 이상으로 위치해 있을 때, 적, 나무, 유리 충격으로 날아간다.


//새 폭발 범위에 따른 피해. 파괴 또는 충격
void ARIM_BirdBlack::ExplosionDamage()
{
	//충돌 정보
	TArray<FOverlapResult> hitInfos;

	//검은새 위치
	FVector center = meshBlack->GetComponentLocation();

	//검은새 폭발 범위(blastRange)
	FCollisionShape blastCollision = FCollisionShape::MakeSphere(blastRange);

	//★★★???
	FCollisionObjectQueryParams objectQuerry;
	//★★★???
	FCollisionQueryParams params;
	params.AddIgnoredActor(this);
	//★★★???
	objectQuerry.AddObjectTypesToQuery(ECC_WorldDynamic);

	//폭발 범위 그리기
	//DrawDebugSphere(GetWorld(), center, blastCollision.GetSphereRadius(), 50, FColor::Cyan, true);

	//Ignore 빼고 blastRange(폭발 범위) 안에 있는 모든 물체를 다 체크 한다
	if (GetWorld()->OverlapMultiByObjectType(hitInfos, center, FQuat::Identity, objectQuerry, FCollisionShape::MakeSphere(blastRange), params))
	{
		//★★★???
		for (FOverlapResult& hit : hitInfos) // [i] = FOverlapResult& hit
		{
			hit.GetActor()->GetActorLocation();
			ARIM_Pig* pigTNT = Cast<ARIM_Pig>(hit.GetActor());
			AKYI_Wood* woodTNT = Cast<AKYI_Wood>(hit.GetActor());
			AKYI_Glass* glassTNT = Cast<AKYI_Glass>(hit.GetActor());

			if (500 > 100) //폭발 범위가 blastRangeDie 이하 일 때, 파괴된다. ★★★수정 필요
			{
				if (pigTNT != nullptr) //돼지
				{
					UE_LOG(LogTemp, Warning, TEXT("Pig ---> Black Explosion ---> Pig Destory !!!!!!!!!!"));
					pigTNT->Destroy();
				}
				else if (woodTNT != nullptr) //나무
				{
					UE_LOG(LogTemp, Warning, TEXT("Wood ---> Black Explosion ---> Wood Destory !!!!!!!!!!"));
					woodTNT->Destroy();
				}
				else if (glassTNT != nullptr) //유리
				{
					UE_LOG(LogTemp, Warning, TEXT("Glass ---> Black Explosion ---> Glass Destory !!!!!!!!!!"));
					glassTNT->Destroy();
				}
			}
			else //폭발 범위가 blastRangeDie 이상 일 때, 충격이 발생한다. ★★★수정 필요
			{
				if (pigTNT != nullptr) //돼지
				{
					UE_LOG(LogTemp, Warning, TEXT("Pig ---> Black Explosion ---> Pig Impulse !!!!!!!!!!"));
					pigTNT->compCollision->AddRadialImpulse(GetActorLocation(), blastRange, ImpulseRange, ERadialImpulseFalloff::RIF_Constant, true);
				}
// * 				else if (woodTNT != nullptr) //나무
// * 				{
// * 					UE_LOG(LogTemp, Warning, TEXT("Wood ---> Black Explosion ---> Wood Impulse !!!!!!!!!!"));
// * 					woodTNT->compCollision->AddRadialImpulse(GetActorLocation(), blastRange, ImpulseRange, ERadialImpulseFalloff::RIF_Constant, true);
// * 				}
// * 				else if (glassTNT != nullptr) //유리
// * 				{
// * 					UE_LOG(LogTemp, Warning, TEXT("Glass ---> Black Explosion ---> Glass Impulse !!!!!!!!!!"));
// * 					glassTNT->compCollision->AddRadialImpulse(GetActorLocation(), blastRange, ImpulseRange, ERadialImpulseFalloff::RIF_Constant, true);
// * 				}
			}
		}
	}
}