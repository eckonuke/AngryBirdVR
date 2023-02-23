// Fill out your copyright notice in the Description page of Project Settings.


#include "RIM_Pig.h"
#include <Components/CapsuleComponent.h>
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
	compCollision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	compCollision->SetupAttachment(RootComponent);
	compCollision->SetSphereRadius(65);
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
	compCollision->OnComponentHit.AddDynamic(this, &ARIM_Pig::ComponentHitBird); //새 -----> 적
	compCollision->OnComponentHit.AddDynamic(this, &ARIM_Pig::ComponentHitObject); //오브젝트(나무, 유리) -----> 적
	//compCollision->OnComponentBeginOverlap.AddDynamic(this, &ARIM_Pig::ComponentBeginOverlapEnemy) //적 낙하 ★★★일단 오버랩으로 진행. OnComponentHit 추후 확인
	player = Cast<ARIM_Player>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
}

// Called every frame
void ARIM_Pig::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//조건에 따른 죽음
	Damaged();

}


//[적(돼지)이 죽는 조건]
//1. 새가 적에게 닿는다. 적이 반드시 죽는다.(없어진다)
//2. 적이 오브젝트(나무, 유리 등)에 닿는다. 일정 충격 이상일 경우 적이 죽는다.(없어진다)
//3. 적이 땅에 닿는다. 적이 반드시 죽는다. ---> 킬존 만들어서 구현


//조건에 따른 죽음
void ARIM_Pig::Damaged()
{
	if (redBirdAttack == true || yellowBirdAttack == true || blueBirdAttack == true || blackBierdAttack == true) //새가 적에게 닿으면
	{
		UE_LOG(LogTemp, Warning, TEXT("Bird Attack -----> Enemy Destroy !!!!!!!!!!"));
		Die(); //적이 반드시 죽는다
 	}
	else if (woodAttack == true) //나무가 적에게 닿았을 때
	{ 	
		//if () //나무 collision 의 충격? 속도? 가 OOO 보다 크면
		//{
			UE_LOG(LogTemp, Warning, TEXT("Wood Attack -----> Enemy Destroy !!!!!!!!!!"));
			Die(); //적이 죽는다
		//}
	}
	else if (glassAttack == true) //유리가 적에게 닿았을 때
	{
		//if () //유리(나무보다 약함) collision 의 충격? 속도? 가 OOO 보다 크면
		//{
			UE_LOG(LogTemp, Warning, TEXT("Glass Attack -----> Enemy Destroy !!!!!!!!!!"));
			Die(); //적이 죽는다
		//}
	}
// 	else if (enemyFall == true) //적이 떨어질 때
// 	{
// 		if ()//적 collision 의 충격? 속도? 가 OOO 보다 크면
// 		{
// 			Die(); //적이 죽는다
// 		}
// 	}
}


//새 -----> 적
void ARIM_Pig::ComponentHitBird(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (Hit.GetActor()->GetName().Contains(TEXT("red"))) //빨간 새가 적과 닿으면
 	{
		AKYI_AngryRed* redOverlap = Cast<AKYI_AngryRed>(OtherActor);
		redBirdAttack = true;

		UE_LOG(LogTemp, Warning, TEXT("Red Bird ---> Overlap ---> Enemy !!!!!!!!!!"));
	}
	else if (Hit.GetActor()->GetName().Contains(TEXT("yellow"))) //노란 새가 적과 닿으면
	{
		AKYI_AngryChuck* yellowOverlap = Cast<AKYI_AngryChuck>(OtherActor);
		yellowBirdAttack = true;

		UE_LOG(LogTemp, Warning, TEXT("Yellow Bird ---> Overlap ---> Enemy !!!!!!!!!!"));
	}
	else if (Hit.GetActor()->GetName().Contains(TEXT("blue"))) //파란 새가 적과 닿으면
	{
		ARIM_BirdBlue* blueOverlap = Cast<ARIM_BirdBlue>(OtherActor);
		blueBirdAttack = true;

		UE_LOG(LogTemp, Warning, TEXT("Blue Bird ---> Overlap ---> Enemy !!!!!!!!!!"));
	}
	else if (Hit.GetActor()->GetName().Contains(TEXT("black"))) //검은 새가 적과 닿으면
	{
		ARIM_BirdBlack* blackOverlap = Cast<ARIM_BirdBlack>(OtherActor);
		blackBierdAttack = true;

		UE_LOG(LogTemp, Warning, TEXT("Black Bird ---> Overlap ---> Enemy !!!!!!!!!!"));
	}
}


//오브젝트 -----> 적
 void ARIM_Pig::ComponentHitObject(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{	
	UE_LOG(LogTemp, Warning, TEXT("Pig hit power :%f"), Hit.ImpactNormal.Length());
	if (Hit.GetActor()->GetName().Contains(TEXT("Wood"))) //오브젝트 "나무"에 닿으면
	{
		AKYI_Wood* woodOverlap = Cast<AKYI_Wood>(OtherActor);
		woodAttack = true;
	}
	else if (Hit.GetActor()->GetName().Contains(TEXT("Glass"))) //오브젝트 "유리"에 닿으면
	{
		AKYI_Glass* glassOverlap = Cast<AKYI_Glass>(OtherActor);
		glassAttack = true;

		UE_LOG(LogTemp, Warning, TEXT("Glass ---> Overlap ---> Enemy !!!!!!!!!!"));
	}
}


//적 낙하 -----> 떨어져서 오브젝트 등에 부딪힌다
// void ARIM_Pig::ComponentBeginOverlapEnemy(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
// {
// 
// 	enemyFall = true;
// 
// }


//죽음
void ARIM_Pig::Die()
{
	//player->score += 5000;
	UGameplayStatics::PlaySound2D(GetWorld(), dieSound, 20);
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), dieEffect, GetActorLocation(), FRotator::ZeroRotator, true, EPSCPoolMethod::None, true);
	player->score += 5000;
	Destroy();
}