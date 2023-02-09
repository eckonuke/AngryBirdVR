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

	//콜리전
	compCollision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	compCollision->SetupAttachment(RootComponent);
	compCollision->SetSphereRadius(80);
	//compCollision-> //콜리전

	//메시
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
	
	compCollision->OnComponentBeginOverlap.AddDynamic(this, &ARIM_Pig::ComponentBeginOverlapBird); //새 -----> 적
	//compCollision->OnComponentBeginOverlap.AddDynamic(this, ARIM_Pig::ComponentBeginOverlapObject); //오브젝트 -----> 적
	//compCollision->OnComponentHit.AddDynamic(this, ARIM_Pig::ComponentHitEnemy) //적 낙하
}

// Called every frame
void ARIM_Pig::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Damaged();

}


//[적이 죽는 경우]
//1. 새가 적에게 닿으면 적이 반드시 죽는다.
//2. 오브젝트(나무, 유리 등)가 적에게 닿았을 때 오브젝트의 충격?속도?가 OOO 보다 크면 적이 죽는다.
//3. 적이 낙하하면 떨어질 때 충격?속도?가 000 보다 크면 적가 죽는다.
//4. 적이 땅에 닿으면 반드시 죽는다. ---> 킬존 만들어서 구현


//조건에 따른 죽음
void ARIM_Pig::Damaged()
{
	if (birdAttack == true) //새가 적에게 닿으면
	{
		UE_LOG(LogTemp, Warning, TEXT("Bird Attack -----> Enemy Die!!!!!!!!!!"));
		Die(); //적이 반드시 죽는다
 	}
// 	else if (IsObjectAttack == true) //오브젝트(나무, 유리 등)가 적에게 닿았을 때
// 	{ 	
// 		if ()//오브젝트 collision 의 충격? 속도? 가 OOO 보다 크면
// 		{
// 			Die(); //적이 죽는다
// 		}
// 	}
// 	else if (EnemyFall == true) //적이 떨어질 때
// 	{
// 		if ()//적 collision 의 충격? 속도? 가 OOO 보다 크면
// 		{
// 			Die(); //적이 죽는다
// 		}
// 	}
}


//새 -----> 적
void ARIM_Pig::ComponentBeginOverlapBird(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->GetName().Contains(TEXT("BirdBlue"))) //새가 적과 닿으면
 	{
 		blue = Cast<ARIM_BirdBlue>(OtherActor);
		birdAttack = true;

		UE_LOG(LogTemp, Warning, TEXT("Bird ---> Overlap ---> Enemy !!!!!!!!!!"));
	}
}


//오브젝트 -----> 적
// void ARIM_Pig::ComponentBeginOverlapObject(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
// {
// 	if (OtherActor->GetName().Contains(TEXT("Wood"))) //오브젝트에 닿으면 ★★★일단 '나무'로 세팅
// 	{
// 		wood = Cast<AKYI_Wood>(OtherActor);
// 		ObjectAttack = true;
// 	}
// }


//적 낙하
// void ARIM_Pig::ComponentHitEnemy() //★★★ 코드 필요
// {
// 
// 	EnemyFall = true;
// 
// }


//죽음
void ARIM_Pig::Die()
{
	Destroy();
}