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
#include "RIM_Player.h"



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
	compCollision->OnComponentHit.AddDynamic(this, &ARIM_TNT::ComponentHitObject); //������Ʈ(����, ����, ����) -----> ��ź
	player = Cast<ARIM_Player>(GetWorld()->GetFirstPlayerController()->GetPawn());
}

// Called every frame
void ARIM_TNT::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
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
			if (hit.GetActor() != nullptr) {
				FString name = hit.GetActor()->GetName();
				if (name.Contains("Angry") || name.Contains("Glass") || name.Contains("Wood") || name.Contains("Pig")) {
					double distance = FVector::Distance(GetActorLocation(), hit.GetActor()->GetActorLocation());
					UE_LOG(LogTemp, Warning, TEXT("%f"), distance);
					if (distance <= blastRangeDie) //���� ������ blastRangeDie ���� �� ��, �ı��ȴ�. �ڡڡڼ��� �ʿ�
					{
						if (name.Contains("Pig")) {
							player->score += 5000;
						}
						else if (name.Contains("Wood") || name.Contains("Glass")) {
							player->score += 500;
						}
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
}

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