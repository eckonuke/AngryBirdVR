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
	compCollision->SetBoxExtent(FVector(35));

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
	//compCollision->OnComponentHit.AddDynamic(this, &ARIM_TNT::ComponentHitBird); //�� -----> ��ź
	compCollision->OnComponentHit.AddDynamic(this, &ARIM_TNT::ComponentHitObject); //������Ʈ(����, ����, ����) -----> ��ź



}

// Called every frame
void ARIM_TNT::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//Shoot();
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
	FVector center = GetActorLocation(); 

	//TNT ���� ����(blastRange)
	FCollisionShape blastCollision = FCollisionShape::MakeSphere(blastRange);
	FCollisionObjectQueryParams objectQuerry;
	objectQuerry.AddObjectTypesToQuery(ECC_WorldDynamic);
	objectQuerry.AddObjectTypesToQuery(ECC_Destructible);
	FCollisionQueryParams params;
	params.AddIgnoredActor(this);
	//�ڡڡ�???

	//���� ���� �׸���
	DrawDebugSphere(GetWorld(), center, blastCollision.GetSphereRadius(), 50, FColor::Cyan, true);

	//Ignore ���� blastRange(���� ����) �ȿ� �ִ� ��� ��ü�� �� üũ �Ѵ�
	if (GetWorld()->OverlapMultiByObjectType(hitInfos, center, FQuat::Identity, objectQuerry, FCollisionShape::MakeSphere(blastRange), params))
	{
		//�ڡڡ�???
		for (FOverlapResult& hit : hitInfos) // [i] = FOverlapResult& hit
		{
			FString name = hit.GetActor()->GetName();
			if (name.Contains("Angry") || name.Contains("Glass") || name.Contains("Wood") || name.Contains("Pig")) {
				double distance = FVector::Distance(GetActorLocation(), hit.GetActor()->GetActorLocation());
				UE_LOG(LogTemp, Warning, TEXT("%f"), distance);
				if (distance <= blastRangeDie) //���� ������ blastRangeDie ���� �� ��, �ı��ȴ�. �ڡڡڼ��� �ʿ�
				{
					hit.GetActor()->Destroy();
				}
				else //���� ������ blastRangeDie �̻� �� ��, ����� �߻��Ѵ�. �ڡڡڼ��� �ʿ�
				{
					glass = Cast<AKYI_Glass>(hit.GetActor());
					wood = Cast<AKYI_Wood>(hit.GetActor());
					pig = Cast<ARIM_Pig>(hit.GetActor());
					if (glass) {
						glass->boxComp->AddRadialImpulse(GetActorLocation(), 1000.0f, 5000.0f, ERadialImpulseFalloff::RIF_Linear, true);
					}
					else if (wood) {
						wood->boxComp->AddRadialImpulse(GetActorLocation(), 1000.0f, 5000.0f, ERadialImpulseFalloff::RIF_Linear, true);
					}
					else if (pig) {
						pig->compCollision->AddRadialImpulse(GetActorLocation(), 1000.0f, 5000.0f, ERadialImpulseFalloff::RIF_Linear, true);
					}
				}

			}
		}
	}
}


////���ǿ� ���� ��ź�� ������
//void ARIM_TNT::Shoot()
//{
//	if (redBirdAttack == true || yellowBirdAttack == true || blueBirdAttack == true || blackBierdAttack == true) //���� ��ź���� ������
//	{
//		UE_LOG(LogTemp, Warning, TEXT("Bird Attack -----> TNT Destroy !!!!!!!!!!"));
//		ExplosionDamage();
//		Die(); //��ź�� ������. ��������
//	}
//	else if (woodAttack == true) //������ ��ź���� ����� ��
//	{
//		//if () //���� collision �� ���? �ӵ�? �� OOO ���� ũ��
//		//{
//		UE_LOG(LogTemp, Warning, TEXT("Wood Attack -----> TNT Destroy !!!!!!!!!!"));
//		ExplosionDamage();
//		Die(); //��ź�� ������. ��������
//		//}
//	}
//	else if (glassAttack == true) //������ ��ź���� ����� ��
//	{
//		//if () //����(�������� ����) collision �� ���? �ӵ�? �� OOO ���� ũ��
//		//{
//		UE_LOG(LogTemp, Warning, TEXT("Glass Attack -----> TNT Destroy !!!!!!!!!!"));
//		ExplosionDamage();
//		Die(); //��ź�� ������. ��������
//		//}
//	}
//	else if (pigAttack == true) //������ ��ź���� ����� ��
//	{
//		UE_LOG(LogTemp, Warning, TEXT("Pig Attack -----> TNT Destroy !!!!!!!!!!"));
//		ExplosionDamage();
//		Die(); //��ź�� ������. ��������
//	}
//}


////�� -----> ��ź
//void ARIM_TNT::ComponentHitBird(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
//{
//	if (Hit.GetActor()->GetName().Contains(TEXT("red"))) //���� ���� ��ź�� ������
//	{
//		AKYI_AngryRed* redOverlap = Cast<AKYI_AngryRed>(OtherActor);
//		redBirdAttack = true;
//
//		UE_LOG(LogTemp, Warning, TEXT("Red Bird ---> Overlap ---> TNT !!!!!!!!!!"));
//	}
//	else if (Hit.GetActor()->GetName().Contains(TEXT("yellow"))) //��� ���� ��ź�� ������
//	{
//		AKYI_AngryChuck* yellowOverlap = Cast<AKYI_AngryChuck>(OtherActor);
//		yellowBirdAttack = true;
//
//		UE_LOG(LogTemp, Warning, TEXT("Yellow Bird ---> Overlap ---> TNT !!!!!!!!!!"));
//	}
//	else if (Hit.GetActor()->GetName().Contains(TEXT("blue"))) //�Ķ� ���� ��ź�� ������
//	{
//		ARIM_BirdBlue* blueOverlap = Cast<ARIM_BirdBlue>(OtherActor);
//		blueBirdAttack = true;
//
//		UE_LOG(LogTemp, Warning, TEXT("Blue Bird ---> Overlap ---> TNT !!!!!!!!!!"));
//	}
//	else if (Hit.GetActor()->GetName().Contains(TEXT("black"))) //���� ���� ��ź�� ������
//	{
//		ARIM_BirdBlack* blackOverlap = Cast<ARIM_BirdBlack>(OtherActor);
//		blackBierdAttack = true;
//
//		UE_LOG(LogTemp, Warning, TEXT("Black Bird ---> Overlap ---> TNT !!!!!!!!!!"));
//	}
//}


//������Ʈ -----> ��ź
void ARIM_TNT::ComponentHitObject(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	FString name = Hit.GetActor()->GetName();
	if (name.Contains("Angry") || name.Contains("Glass") || name.Contains("Wood") || name.Contains("Pig")) {
		UE_LOG(LogTemp, Warning, TEXT("Hit by %s"), *OtherActor->GetName());
		ExplosionDamage();
		Die();
	}
}


//��ź ��������
void ARIM_TNT::Die() {
	UGameplayStatics::PlaySound2D(GetWorld(), explosionSound, 5);
	this->Destroy();
}