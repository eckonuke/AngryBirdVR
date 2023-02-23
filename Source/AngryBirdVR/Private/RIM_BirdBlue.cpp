// Fill out your copyright notice in the Description page of Project Settings.


#include "RIM_BirdBlue.h"
#include <Components/SphereComponent.h>
#include <Components/StaticMeshComponent.h>
#include <GameFramework/ProjectileMovementComponent.h>
#include "RIM_Player.h"
#include <Components/SkeletalMeshComponent.h>
#include "KYI_Glass.h"
#include "RIM_Pig.h"
#include "RIM_TNT.h"


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
	meshBlue = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("BlueBird"));
	meshBlue->SetupAttachment(compCollision);
// 	ConstructorHelpers::FObjectFinder<USkeletalMesh> tempBird(TEXT("/Script/Engine.StaticMesh'/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere'")); //▶추후 수정
// 	if (tempBird.Succeeded())
// 	{
// 		meshBlue->USkeletalMesh(tempBird.Object);
// 	}
	meshBlue->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	//meshBlue->SetRelativeLocation(FVector(0, 0, 0)); //▶추후 수정
	meshBlue->SetRelativeScale3D(FVector(0.11f)); //▶추후 수정
	meshBlue->SetRelativeLocation(FVector(0, 0, -6));
	meshBlue->SetRelativeRotation(FRotator(0, 90, 0));

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
void ARIM_BirdBlue::BeginPlay()
{
	Super::BeginPlay();
	compCollision->OnComponentBeginOverlap.AddDynamic(this, &ARIM_BirdBlue::ComponentHitObject);
	//일정 시간 지난 후 새 파괴
	SetLifeSpan(4);
}

// Called every frame
void ARIM_BirdBlue::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARIM_BirdBlue::ComponentHitObject(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit)
{
	AActor* actor = Hit.GetActor();
	if (actor) {
		FString name = actor->GetName();
		AKYI_Glass* glass = Cast<AKYI_Glass>(actor);
		ARIM_Pig* pig = Cast<ARIM_Pig>(actor);
		ARIM_TNT* tnt = Cast<ARIM_TNT>(actor);
		if (glass) {
			glass->Die();
		}
		else if (pig) {
			pig->Die();
		}
		else if (tnt) {
			tnt->Die();
		}
	}
}