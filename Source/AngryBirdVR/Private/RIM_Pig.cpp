// Fill out your copyright notice in the Description page of Project Settings.


#include "RIM_Pig.h"
#include <Components/CapsuleComponent.h>
#include <Components/BoxComponent.h>
#include <Components/SphereComponent.h>
#include <Components/StaticMeshComponent.h>
#include "KYI_AngryRed.h"
#include "KYI_AngryChuck.h"
#include "RIM_BirdBlue.h"
#include "RIM_BirdBlack.h"
#include <GameFramework/Character.h>
#include "KYI_Wood.h"
#include "KYI_Glass.h"
#include "Kismet/GameplayStatics.h"
#include <Sound/SoundBase.h>
#include "RIM_Player.h"
#include <Particles/ParticleSystemComponent.h>

// Sets default values
ARIM_Pig::ARIM_Pig()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//�ݸ���
	compCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));
	compCollision->SetupAttachment(RootComponent);
	compCollision->SetBoxExtent(FVector(25));
	SetRootComponent(compCollision);
	//compCollision-> //�ݸ���
	compCollision->SetSimulatePhysics(true);
	compCollision->SetNotifyRigidBodyCollision(true);
	compCollision->BodyInstance.SetCollisionProfileName("BlockAllDynamic");


	//�޽�
	compMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Enemy"));
	compMesh->SetupAttachment(compCollision);
	compMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	ConstructorHelpers::FObjectFinder<UStaticMesh> tempMesh(TEXT("/Script/Engine.StaticMesh'/Game/Resource/Pig/Pig.Pig'"));
	if (tempMesh.Succeeded())
	{
		compMesh->SetStaticMesh(tempMesh.Object);
	}
	compMesh->SetRelativeLocation(FVector(0, 0, -23));
	compMesh->SetRelativeRotation(FRotator(0, 90, 0));
	compMesh->SetRelativeScale3D(FVector(0.05));

	ConstructorHelpers::FObjectFinder<USoundBase> tempSound(TEXT("/Script/Engine.SoundWave'/Game/Resource/Sound/PigDestroySound.PigDestroySound'"));
	if (tempSound.Succeeded()) {
		dieSound = tempSound.Object;
	}

	//����Ʈ
	ConstructorHelpers::FObjectFinder<UParticleSystem> tempEffect(TEXT("/Script/Engine.ParticleSystem'/Game/Realistic_Starter_VFX_Pack_Vol2/Particles/Smoke/P_Steam_A.P_Steam_A'"));
	if (tempEffect.Succeeded())
	{
		dieEffect = tempEffect.Object;
	}


}

// Called when the game starts or when spawned
void ARIM_Pig::BeginPlay()
{
	Super::BeginPlay();
	//player = Cast<ARIM_Player>(GetOwner());
	compCollision->OnComponentHit.AddDynamic(this, &ARIM_Pig::ComponentHitObject); //������Ʈ(����, ����) -----> ��
	//compCollision->OnComponentBeginOverlap.AddDynamic(this, &ARIM_Pig::ComponentBeginOverlapEnemy) //�� ���� �ڡڡ��ϴ� ���������� ����. OnComponentHit ���� Ȯ��
	player = Cast<ARIM_Player>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
}

// Called every frame
void ARIM_Pig::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


//[��(����)�� �״� ����]
//1. ���� ������ ��´�. ���� �ݵ�� �״´�.(��������)
//2. ���� ������Ʈ(����, ���� ��)�� ��´�. ���� ��� �̻��� ��� ���� �״´�.(��������)
//3. ���� ���� ��´�. ���� �ݵ�� �״´�. ---> ų�� ���� ����

 void ARIM_Pig::ComponentHitObject(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{	
	 AActor* actor = Hit.GetActor();
	 if (actor) {
		 if (actor->GetVelocity().Length() > 300) {
			 FString name = actor->GetName();
			 if (name.Contains("Angry") || name.Contains("Glass") || name.Contains("Wood") || name.Contains("Pig")) {
				 Die();
			 }
		 }
	 }
}

//����
void ARIM_Pig::Die()
{
	//player->score += 5000;
	UGameplayStatics::PlaySound2D(GetWorld(), dieSound, 20);
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), dieEffect, GetActorLocation(), FRotator::ZeroRotator, true, EPSCPoolMethod::None, true);
	player->score += 5000;
	Destroy();
}