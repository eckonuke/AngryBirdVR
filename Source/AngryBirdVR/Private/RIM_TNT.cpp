// Fill out your copyright notice in the Description page of Project Settings.


#include "RIM_TNT.h"
#include <Components/BoxComponent.h>
#include <Components/SkeletalMeshComponent.h>
#include <Components/SphereComponent.h>
#include "DrawDebugHelpers.h"
#include "KYI_AngryRed.h"
#include "KYI_AngryChuck.h"
#include "RIM_BirdBlue.h"
#include "RIM_BirdBlack.h"
#include "KYI_Wood.h"
#include "KYI_Glass.h"
#include "RIM_Pig.h"
#include <Kismet/GameplayStatics.h>



// Sets default values
ARIM_TNT::ARIM_TNT()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	compCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));
	compCollision->SetupAttachment(RootComponent);
	//compCollision-> //�ݸ���

	meshTNT = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("TNT"));
	meshTNT->SetupAttachment(compCollision);
	ConstructorHelpers::FObjectFinder<USkeletalMesh> tempMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/Resource/TNT/Test_Chest_01.Test_Chest_01'"));
	if (tempMesh.Succeeded())
	{
		meshTNT->SetSkeletalMesh(tempMesh.Object);
	}
	meshTNT->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	ConstructorHelpers::FObjectFinder<USoundBase> tempSound(TEXT("/Script/Engine.SoundWave'/Game/Resource/Sound/TNTExplosionSound.TNTExplosionSound'"));
	if (tempSound.Succeeded()) {
		explosionSound = tempSound.Object;
	}
}

// Called when the game starts or when spawned
void ARIM_TNT::BeginPlay()
{
	Super::BeginPlay();

	compCollision->OnComponentBeginOverlap.AddDynamic(this, &ARIM_TNT::ComponentBeginOverlapBird); //�� -----> ��ź
	compCollision->OnComponentBeginOverlap.AddDynamic(this, &ARIM_TNT::ComponentBeginOverlapObject); //������Ʈ(����, ����, ����) -----> ��ź



}

// Called every frame
void ARIM_TNT::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Shoot();
	


}


//[��ź�� ������ ����]
//1. ���� ��ź�� ��´�. ������ ������.(��������)
//2. ��ź�� ������Ʈ(����, ����, ��ź ��)�� ��´�. ���� ��� �̻��� ��� ������.(��������)
//3. ��ź�� ���� ��´�. ������ ������(��������). ---> ų�� ���� ����

//[��ź�� ������ �߻��ϴ� ��]
//1. blastRange(��ź ����) ���� ��ź�� ���� �Ÿ� ���Ϸ� ��ġ�� ���� ��, ��, ����, ���� �ı��ȴ�.
//2. blastRange(��ź ����) ���� ��ź�� ���� �Ÿ� �̻����� ��ġ�� ���� ��, ��, ����, ���� ������� ���ư���.


//��ź�� ������ ���� ����. �ı� �Ǵ� ���
void ARIM_TNT::ExplosionDamage()
{
	//�浹 ����
	TArray<FOverlapResult> hitInfos;

	//TNT ��ġ �ڡڡڿ� ���� �����̼� �� ���?
	FVector center = meshTNT->GetComponentLocation(); 

	//TNT ���� ����(blastRange)
	FCollisionShape blastCollision = FCollisionShape::MakeSphere(blastRange);

	//�ڡڡ�???
	FCollisionObjectQueryParams objectQuerry;
	//�ڡڡ�???
	FCollisionQueryParams params; 
	params.AddIgnoredActor(this);
	//�ڡڡ�???
	objectQuerry.AddObjectTypesToQuery(ECC_WorldDynamic);

	//���� ���� �׸���
	DrawDebugSphere(GetWorld(), center, blastCollision.GetSphereRadius(), 50, FColor::Cyan, true);

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
					UE_LOG(LogTemp, Warning, TEXT("Pig ---> TNT ---> Pig Destory !!!!!!!!!!"));
					pigTNT->Destroy();
				}
				else if (woodTNT != nullptr) //����
				{
					UE_LOG(LogTemp, Warning, TEXT("Wood ---> TNT ---> Wood Destory !!!!!!!!!!"));
					Destroy();
				}
				else if (glassTNT != nullptr) //����
				{
					UE_LOG(LogTemp, Warning, TEXT("Glass ---> TNT ---> Glass Destory !!!!!!!!!!"));
					Destroy();
				}
			}
			else //���� ������ blastRangeDie �̻� �� ��, ����� �߻��Ѵ�. �ڡڡڼ��� �ʿ�
			{
				if (pigTNT != nullptr) //����
				{
					UE_LOG(LogTemp, Warning, TEXT("Pig ---> TNT ---> Pig Impulse !!!!!!!!!!"));
					pigTNT->compCollision->AddRadialImpulse(GetActorLocation(), blastRange, ImpulseRange, ERadialImpulseFalloff::RIF_Constant, true);
				}
// 				else if (woodTNT != nullptr) //����
// 				{
// 					UE_LOG(LogTemp, Warning, TEXT("Wood ---> TNT ---> Wood Impulse !!!!!!!!!!"));
// 					woodTNT->compCollision->AddRadialImpulse(GetActorLocation(), blastRange, ImpulseRange, ERadialImpulseFalloff::RIF_Constant, true);
// 				}
// 				else if (glassTNT != nullptr) //����
// 				{
// 					UE_LOG(LogTemp, Warning, TEXT("Glass ---> TNT ---> Glass Impulse !!!!!!!!!!"));
// 					glassTNT->compCollision->AddRadialImpulse(GetActorLocation(), blastRange, ImpulseRange, ERadialImpulseFalloff::RIF_Constant, true);
// 				}
			}
		}
	}
}


//���ǿ� ���� ��ź�� ������
void ARIM_TNT::Shoot()
{
	if (redBirdAttack == true || yellowBirdAttack == true || blueBirdAttack == true || blackBierdAttack == true) //���� ��ź���� ������
	{
		UE_LOG(LogTemp, Warning, TEXT("Bird Attack -----> TNT Destroy !!!!!!!!!!"));
		ExplosionDamage();
		Die(); //��ź�� ������. ��������
	}
	else if (woodAttack == true) //������ ��ź���� ����� ��
	{
		//if () //���� collision �� ���? �ӵ�? �� OOO ���� ũ��
		//{
		UE_LOG(LogTemp, Warning, TEXT("Wood Attack -----> TNT Destroy !!!!!!!!!!"));
		ExplosionDamage();
		Die(); //��ź�� ������. ��������
		//}
	}
	else if (glassAttack == true) //������ ��ź���� ����� ��
	{
		//if () //����(�������� ����) collision �� ���? �ӵ�? �� OOO ���� ũ��
		//{
		UE_LOG(LogTemp, Warning, TEXT("Glass Attack -----> TNT Destroy !!!!!!!!!!"));
		ExplosionDamage();
		Die(); //��ź�� ������. ��������
		//}
	}
	else if (pigAttack == true) //������ ��ź���� ����� ��
	{
		UE_LOG(LogTemp, Warning, TEXT("Pig Attack -----> TNT Destroy !!!!!!!!!!"));
		ExplosionDamage();
		Die(); //��ź�� ������. ��������
	}
}


//�� -----> ��ź
void ARIM_TNT::ComponentBeginOverlapBird(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->GetName().Contains(TEXT("red"))) //���� ���� ��ź�� ������
	{
		AKYI_AngryRed* redOverlap = Cast<AKYI_AngryRed>(OtherActor);
		redBirdAttack = true;

		UE_LOG(LogTemp, Warning, TEXT("Red Bird ---> Overlap ---> TNT !!!!!!!!!!"));
	}
	else if (OtherActor->GetName().Contains(TEXT("yellow"))) //��� ���� ��ź�� ������
	{
		AKYI_AngryChuck* yellowOverlap = Cast<AKYI_AngryChuck>(OtherActor);
		yellowBirdAttack = true;

		UE_LOG(LogTemp, Warning, TEXT("Yellow Bird ---> Overlap ---> TNT !!!!!!!!!!"));
	}
	else if (OtherActor->GetName().Contains(TEXT("blue"))) //�Ķ� ���� ��ź�� ������
	{
		ARIM_BirdBlue* blueOverlap = Cast<ARIM_BirdBlue>(OtherActor);
		blueBirdAttack = true;

		UE_LOG(LogTemp, Warning, TEXT("Blue Bird ---> Overlap ---> TNT !!!!!!!!!!"));
	}
	else if (OtherActor->GetName().Contains(TEXT("black"))) //���� ���� ��ź�� ������
	{
		ARIM_BirdBlack* blackOverlap = Cast<ARIM_BirdBlack>(OtherActor);
		blackBierdAttack = true;

		UE_LOG(LogTemp, Warning, TEXT("Black Bird ---> Overlap ---> TNT !!!!!!!!!!"));
	}
}


//������Ʈ -----> ��ź
void ARIM_TNT::ComponentBeginOverlapObject(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->GetName().Contains(TEXT("Wood"))) //������Ʈ "����"�� ������
	{
		AKYI_Wood* woodOverlap = Cast<AKYI_Wood>(OtherActor);
		woodAttack = true;

		UE_LOG(LogTemp, Warning, TEXT("Wood ---> Overlap ---> TNT !!!!!!!!!!"));
	}
	else if (OtherActor->GetName().Contains(TEXT("Glass"))) //������Ʈ "����"�� ������
	{
		AKYI_Glass* glassOverlap = Cast<AKYI_Glass>(OtherActor);
		glassAttack = true;

		UE_LOG(LogTemp, Warning, TEXT("Glass ---> Overlap ---> TNT !!!!!!!!!!"));
	}
	else if (OtherActor->GetName().Contains(TEXT("Pig"))) //������Ʈ "��"�� ������
	{
		ARIM_Pig* pigOverlap = Cast<ARIM_Pig>(OtherActor);
		pigAttack = true;

		UE_LOG(LogTemp, Warning, TEXT("Pig ---> Overlap ---> TNT !!!!!!!!!!"));
	}
}


//��ź ��������
void ARIM_TNT::Die()
{
	UGameplayStatics::PlaySound2D(GetWorld(), explosionSound, 5);
	Destroy();
}