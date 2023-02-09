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

	//�浹ü
	compCollision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	RootComponent = compCollision; //��Ʈ������Ʈ�� ����. compCollision->SetupAttachment(RootComponent);
	compCollision->SetCollisionProfileName(TEXT("BlockAll"));
	compCollision->SetSphereRadius(10); //���浹ü ũ��. ���� ����
	compCollision->SetSimulatePhysics(true);

	//�ܰ�
	meshBlue = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BlueBird"));
	meshBlue->SetupAttachment(compCollision);
	ConstructorHelpers::FObjectFinder<UStaticMesh> tempBird(TEXT("/Script/Engine.StaticMesh'/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere'")); //������ ����
	if (tempBird.Succeeded())
	{
		meshBlue->SetStaticMesh(tempBird.Object);
	}
	meshBlue->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	//meshBlue->SetRelativeLocation(FVector(0, 0, 0)); //������ ����
	meshBlue->SetRelativeScale3D(FVector(0.08f)); //������ ����

	//�߻�ü �ڡڡڿ��� ���ϸ� �ʿ������ �ϴ� ����
	compMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movement"));
	compMovement->SetUpdatedComponent(compCollision);
	compMovement->InitialSpeed = 2000; //�ʱ�ӵ�. ���ʿ�� ���� ����
	compMovement->MaxSpeed = 5000; //�ִ�ӵ�. ���ʿ�� ���� ����
	compMovement->bShouldBounce = true; //�ݵ�����. ƨ��� ����
	compMovement->Bounciness = 0.5f; //�󸶳� �� ƨ�⿡ �� ���ΰ�. �ݵ�. ź��. ���ʿ�� ���� ����
	//InitialLifeSpan = 10.0f; //���� �ð�. ���ʿ�� ���� ����

}

// Called when the game starts or when spawned
void ARIM_BirdBlue::BeginPlay()
{
	Super::BeginPlay();

	//���� �ð� ���� �� �� �ı�
	//FTimerHandle deathTimer;
	//GetWorld()->GetTimerManager().SetTimer(deathTimer, this, &ARIM_BirdBlue::Death, delayDeathTime, false); //Ÿ�̸�

	
}

// Called every frame
void ARIM_BirdBlue::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//�չ������� ��� �̵� �ڡڡڿ��� ���ϸ� �ʿ������ �ϴ� ����
	//P = P0 + vt
	//FVector p0 = GetActorLocation();
	//FVector vt = GetActorLocation() * 2000 * DeltaTime;

}

//���� �ð� ���� �� �� �ı�
//void ARIM_BirdBlue::Death()
//{
//	Destroy();
//}

