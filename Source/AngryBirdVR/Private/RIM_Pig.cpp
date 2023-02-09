// Fill out your copyright notice in the Description page of Project Settings.


#include "RIM_Pig.h"
#include <Components/CapsuleComponent.h>
#include <Components/SphereComponent.h>
#include <Components/StaticMeshComponent.h>
#include "RIM_BirdBlue.h"
#include <GameFramework/Character.h>
#include "KYI_Wood.h"

// Sets default values
ARIM_Pig::ARIM_Pig()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//�ݸ���
	compCollision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	compCollision->SetupAttachment(RootComponent);
	compCollision->SetSphereRadius(80);
	//compCollision-> //�ݸ���

	//�޽�
	compMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Enemy"));
	compMesh->SetupAttachment(compCollision);
	compMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	ConstructorHelpers::FObjectFinder<UStaticMesh> tempMesh(TEXT("/Script/Engine.StaticMesh'/Game/Resource/Pig/Pig.Pig'"));
	if (tempMesh.Succeeded())
	{
		compMesh->SetStaticMesh(tempMesh.Object);
	}
	compMesh->SetRelativeLocation(FVector(0, 0, -50));
	compMesh->SetWorldRotation(FRotator(0, 0, 90));


}

// Called when the game starts or when spawned
void ARIM_Pig::BeginPlay()
{
	Super::BeginPlay();
	
	compCollision->OnComponentBeginOverlap.AddDynamic(this, &ARIM_Pig::ComponentBeginOverlapBird); //�� -----> ��
	//compCollision->OnComponentBeginOverlap.AddDynamic(this, ARIM_Pig::ComponentBeginOverlapObject); //������Ʈ -----> ��
	//compCollision->OnComponentHit.AddDynamic(this, ARIM_Pig::ComponentHitEnemy) //�� ����
}

// Called every frame
void ARIM_Pig::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Damaged();

}


//[���� �״� ���]
//1. ���� ������ ������ ���� �ݵ�� �״´�.
//2. ������Ʈ(����, ���� ��)�� ������ ����� �� ������Ʈ�� ���?�ӵ�?�� OOO ���� ũ�� ���� �״´�.
//3. ���� �����ϸ� ������ �� ���?�ӵ�?�� 000 ���� ũ�� ���� �״´�.
//4. ���� ���� ������ �ݵ�� �״´�. ---> ų�� ���� ����


//���ǿ� ���� ����
void ARIM_Pig::Damaged()
{
	if (birdAttack == true) //���� ������ ������
	{
		UE_LOG(LogTemp, Warning, TEXT("Bird Attack -----> Enemy Die!!!!!!!!!!"));
		Die(); //���� �ݵ�� �״´�
 	}
// 	else if (IsObjectAttack == true) //������Ʈ(����, ���� ��)�� ������ ����� ��
// 	{ 	
// 		if ()//������Ʈ collision �� ���? �ӵ�? �� OOO ���� ũ��
// 		{
// 			Die(); //���� �״´�
// 		}
// 	}
// 	else if (EnemyFall == true) //���� ������ ��
// 	{
// 		if ()//�� collision �� ���? �ӵ�? �� OOO ���� ũ��
// 		{
// 			Die(); //���� �״´�
// 		}
// 	}
}


//�� -----> ��
void ARIM_Pig::ComponentBeginOverlapBird(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->GetName().Contains(TEXT("BirdBlue"))) //���� ���� ������
 	{
 		blue = Cast<ARIM_BirdBlue>(OtherActor);
		birdAttack = true;

		UE_LOG(LogTemp, Warning, TEXT("Bird ---> Overlap ---> Enemy !!!!!!!!!!"));
	}
}


//������Ʈ -----> ��
// void ARIM_Pig::ComponentBeginOverlapObject(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
// {
// 	if (OtherActor->GetName().Contains(TEXT("Wood"))) //������Ʈ�� ������ �ڡڡ��ϴ� '����'�� ����
// 	{
// 		wood = Cast<AKYI_Wood>(OtherActor);
// 		ObjectAttack = true;
// 	}
// }


//�� ����
// void ARIM_Pig::ComponentHitEnemy() //�ڡڡ� �ڵ� �ʿ�
// {
// 
// 	EnemyFall = true;
// 
// }


//����
void ARIM_Pig::Die()
{
	Destroy();
}