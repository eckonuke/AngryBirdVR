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

	//�浹ü
	compCollision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	RootComponent = compCollision; //��Ʈ������Ʈ�� ����. compCollision->SetupAttachment(RootComponent);
	compCollision->SetCollisionProfileName(TEXT("BlockAll"));
	compCollision->SetSphereRadius(10); //���浹ü ũ��. ���� ����
	compCollision->SetSimulatePhysics(true);

	//�ܰ�
	meshBlack = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BlackBird"));
	meshBlack->SetupAttachment(compCollision);
	ConstructorHelpers::FObjectFinder<UStaticMesh> tempBird(TEXT("/Script/Engine.StaticMesh'/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere'")); //������ ����
	if (tempBird.Succeeded())
	{
		meshBlack->SetStaticMesh(tempBird.Object);
	}
	meshBlack->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	//meshBlue->SetRelativeLocation(FVector(0, 0, 0)); //������ ����
	meshBlack->SetRelativeScale3D(FVector(0.08f)); //������ ����

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
void ARIM_BirdBlack::BeginPlay()
{
	Super::BeginPlay();
	
	//���� �ð� ���� �� �� �ı�
	//FTimerHandle deathTimer;
	//GetWorld()->GetTimerManager().SetTimer(deathTimer, this, &ARIM_BirdBlue::Death, delayDeathTime, false); //Ÿ�̸�
}

// Called every frame
void ARIM_BirdBlack::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//�չ������� ��� �̵� �ڡڡڿ��� ���ϸ� �ʿ������ �ϴ� ����
	//P = P0 + vt
	//FVector p0 = GetActorLocation();
	//FVector vt = GetActorLocation() * 2000 * DeltaTime;

}

//���� �ð� ���� �� �� �ı�
//void ARIM_BirdBlack::Death()
//{
//	Destroy();
//}


//[���� ������ �߻��ϴ� ��]
//1. blastRange(��ź ����) ���� ��ź�� ���� �Ÿ� ���Ϸ� ��ġ�� ���� ��, ��, ����, ���� �ı��ȴ�.
//2. blastRange(��ź ����) ���� ��ź�� ���� �Ÿ� �̻����� ��ġ�� ���� ��, ��, ����, ���� ������� ���ư���.


//�� ���� ������ ���� ����. �ı� �Ǵ� ���
void ARIM_BirdBlack::ExplosionDamage()
{
	//�浹 ����
	TArray<FOverlapResult> hitInfos;

	//������ ��ġ
	FVector center = meshBlack->GetComponentLocation();

	//������ ���� ����(blastRange)
	FCollisionShape blastCollision = FCollisionShape::MakeSphere(blastRange);

	//�ڡڡ�???
	FCollisionObjectQueryParams objectQuerry;
	//�ڡڡ�???
	FCollisionQueryParams params;
	params.AddIgnoredActor(this);
	//�ڡڡ�???
	objectQuerry.AddObjectTypesToQuery(ECC_WorldDynamic);

	//���� ���� �׸���
	//DrawDebugSphere(GetWorld(), center, blastCollision.GetSphereRadius(), 50, FColor::Cyan, true);

	//Ignore ���� blastRange(���� ����) �ȿ� �ִ� ��� ��ü�� �� üũ �Ѵ�
	if (GetWorld()->OverlapMultiByObjectType(hitInfos, center, FQuat::Identity, objectQuerry, FCollisionShape::MakeSphere(blastRange), params))
	{
		//�ڡڡ�???
		for (FOverlapResult& hit : hitInfos) // [i] = FOverlapResult& hit
		{
			hit.GetActor()->GetActorLocation();
			ARIM_Pig* pigTNT = Cast<ARIM_Pig>(hit.GetActor());
			AKYI_Wood* woodTNT = Cast<AKYI_Wood>(hit.GetActor());
			AKYI_Glass* glassTNT = Cast<AKYI_Glass>(hit.GetActor());

			if (500 > 100) //���� ������ blastRangeDie ���� �� ��, �ı��ȴ�. �ڡڡڼ��� �ʿ�
			{
				if (pigTNT != nullptr) //����
				{
					UE_LOG(LogTemp, Warning, TEXT("Pig ---> Black Explosion ---> Pig Destory !!!!!!!!!!"));
					pigTNT->Destroy();
				}
				else if (woodTNT != nullptr) //����
				{
					UE_LOG(LogTemp, Warning, TEXT("Wood ---> Black Explosion ---> Wood Destory !!!!!!!!!!"));
					woodTNT->Destroy();
				}
				else if (glassTNT != nullptr) //����
				{
					UE_LOG(LogTemp, Warning, TEXT("Glass ---> Black Explosion ---> Glass Destory !!!!!!!!!!"));
					glassTNT->Destroy();
				}
			}
			else //���� ������ blastRangeDie �̻� �� ��, ����� �߻��Ѵ�. �ڡڡڼ��� �ʿ�
			{
				if (pigTNT != nullptr) //����
				{
					UE_LOG(LogTemp, Warning, TEXT("Pig ---> Black Explosion ---> Pig Impulse !!!!!!!!!!"));
					pigTNT->compCollision->AddRadialImpulse(GetActorLocation(), blastRange, ImpulseRange, ERadialImpulseFalloff::RIF_Constant, true);
				}
// * 				else if (woodTNT != nullptr) //����
// * 				{
// * 					UE_LOG(LogTemp, Warning, TEXT("Wood ---> Black Explosion ---> Wood Impulse !!!!!!!!!!"));
// * 					woodTNT->compCollision->AddRadialImpulse(GetActorLocation(), blastRange, ImpulseRange, ERadialImpulseFalloff::RIF_Constant, true);
// * 				}
// * 				else if (glassTNT != nullptr) //����
// * 				{
// * 					UE_LOG(LogTemp, Warning, TEXT("Glass ---> Black Explosion ---> Glass Impulse !!!!!!!!!!"));
// * 					glassTNT->compCollision->AddRadialImpulse(GetActorLocation(), blastRange, ImpulseRange, ERadialImpulseFalloff::RIF_Constant, true);
// * 				}
			}
		}
	}
}