// Fill out your copyright notice in the Description page of Project Settings.


#include "RIM_BirdBlue.h"
#include <Components/SphereComponent.h>
#include <Components/StaticMeshComponent.h>
#include <GameFramework/ProjectileMovementComponent.h>
#include "RIM_Player.h"


// Sets default values
ARIM_BirdBlue::ARIM_BirdBlue()
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
	meshBlue = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BlueBird"));
	meshBlue->SetupAttachment(compCollision);
	ConstructorHelpers::FObjectFinder<UStaticMesh> tempBird(TEXT("/Script/Engine.StaticMesh'/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere'")); //▶추후 수정
	if (tempBird.Succeeded())
	{
		meshBlue->SetStaticMesh(tempBird.Object);
	}
	meshBlue->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	//meshBlue->SetRelativeLocation(FVector(0, 0, 0)); //▶추후 수정
	meshBlue->SetRelativeScale3D(FVector(0.08f)); //▶추후 수정

	//발사체 ★★★영상에 의하면 필요없으나 일단 넣음
	compMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movement"));
	compMovement->SetUpdatedComponent(compCollision);
	compMovement->InitialSpeed = 2000; //초기속도. ▶필요시 추후 수정
	compMovement->MaxSpeed = 5000; //최대속도. ▶필요시 추후 수정
	compMovement->bShouldBounce = true; //반동여부. 튕기는 여부
	compMovement->Bounciness = 0.5f; //얼마나 잘 튕기에 할 것인가. 반동. 탄성. ▶필요시 추후 수정
	//InitialLifeSpan = 10.0f; //생명 시간. ▶필요시 추후 수정

}

// Called when the game starts or when spawned
void ARIM_BirdBlue::BeginPlay()
{
	Super::BeginPlay();

	//일정 시간 지난 후 새 파괴
	//FTimerHandle deathTimer;
	//GetWorld()->GetTimerManager().SetTimer(deathTimer, this, &ARIM_BirdBlue::Death, delayDeathTime, false); //타이머

	
}

// Called every frame
void ARIM_BirdBlue::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//앞방향으로 계속 이동 ★★★영상에 의하면 필요없으나 일단 넣음
	//P = P0 + vt
	//FVector p0 = GetActorLocation();
	//FVector vt = GetActorLocation() * 2000 * DeltaTime;

}

//일정 시간 지난 후 새 파괴
//void ARIM_BirdBlue::Death()
//{
//	Destroy();
//}

