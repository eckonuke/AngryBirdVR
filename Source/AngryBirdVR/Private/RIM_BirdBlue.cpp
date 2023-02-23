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

	//�浹ü
	compCollision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	RootComponent = compCollision; //��Ʈ������Ʈ�� ����. compCollision->SetupAttachment(RootComponent);
	compCollision->SetCollisionProfileName(TEXT("BlockAll"));
	compCollision->SetSphereRadius(10); //���浹ü ũ��. ���� ����
	compCollision->SetSimulatePhysics(true);

	//�ܰ�
	meshBlue = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("BlueBird"));
	meshBlue->SetupAttachment(compCollision);
// 	ConstructorHelpers::FObjectFinder<USkeletalMesh> tempBird(TEXT("/Script/Engine.StaticMesh'/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere'")); //������ ����
// 	if (tempBird.Succeeded())
// 	{
// 		meshBlue->USkeletalMesh(tempBird.Object);
// 	}
	meshBlue->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	//meshBlue->SetRelativeLocation(FVector(0, 0, 0)); //������ ����
	meshBlue->SetRelativeScale3D(FVector(0.11f)); //������ ����
	meshBlue->SetRelativeLocation(FVector(0, 0, -6));
	meshBlue->SetRelativeRotation(FRotator(0, 90, 0));

	//�߻�ü �ڡڡڿ��� ���ϸ� �ʿ������ �ϴ� ����
	compMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movement"));
	compMovement->SetUpdatedComponent(compCollision);
	compMovement->InitialSpeed = 0; //�ʱ�ӵ�. ���ʿ�� ���� ����
	compMovement->MaxSpeed = 0; //�ִ�ӵ�. ���ʿ�� ���� ����
	compMovement->bShouldBounce = true; //�ݵ�����. ƨ��� ����
	compMovement->Bounciness = 0.5f; //�󸶳� �� ƨ�⿡ �� ���ΰ�. �ݵ�. ź��. ���ʿ�� ���� ����
	//InitialLifeSpan = 10.0f; //���� �ð�. ���ʿ�� ���� ����

}

// Called when the game starts or when spawned
void ARIM_BirdBlue::BeginPlay()
{
	Super::BeginPlay();
	compCollision->OnComponentBeginOverlap.AddDynamic(this, &ARIM_BirdBlue::ComponentHitObject);
	//���� �ð� ���� �� �� �ı�
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