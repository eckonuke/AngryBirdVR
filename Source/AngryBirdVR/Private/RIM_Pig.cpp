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

	//콜리전
	compCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));
	compCollision->SetupAttachment(RootComponent);
	compCollision->SetBoxExtent(FVector(25));
	SetRootComponent(compCollision);
	//compCollision-> //콜리전
	compCollision->SetSimulatePhysics(true);
	compCollision->SetNotifyRigidBodyCollision(true);
	compCollision->BodyInstance.SetCollisionProfileName("BlockAllDynamic");


	//메시
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

	//이펙트
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
	compCollision->OnComponentHit.AddDynamic(this, &ARIM_Pig::ComponentHitObject); //오브젝트(나무, 유리) -----> 적
	//compCollision->OnComponentBeginOverlap.AddDynamic(this, &ARIM_Pig::ComponentBeginOverlapEnemy) //적 낙하 ★★★일단 오버랩으로 진행. OnComponentHit 추후 확인
	player = Cast<ARIM_Player>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
}

// Called every frame
void ARIM_Pig::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


//[적(돼지)이 죽는 조건]
//1. 새가 적에게 닿는다. 적이 반드시 죽는다.(없어진다)
//2. 적이 오브젝트(나무, 유리 등)에 닿는다. 일정 충격 이상일 경우 적이 죽는다.(없어진다)
//3. 적이 땅에 닿는다. 적이 반드시 죽는다. ---> 킬존 만들어서 구현

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

//죽음
void ARIM_Pig::Die()
{
	//player->score += 5000;
	UGameplayStatics::PlaySound2D(GetWorld(), dieSound, 20);
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), dieEffect, GetActorLocation(), FRotator::ZeroRotator, true, EPSCPoolMethod::None, true);
	player->score += 5000;
	Destroy();
}