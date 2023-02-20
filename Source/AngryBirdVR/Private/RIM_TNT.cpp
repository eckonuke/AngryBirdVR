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
	//compCollision-> //콜리전

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

	compCollision->OnComponentBeginOverlap.AddDynamic(this, &ARIM_TNT::ComponentBeginOverlapBird); //새 -----> 폭탄
	compCollision->OnComponentBeginOverlap.AddDynamic(this, &ARIM_TNT::ComponentBeginOverlapObject); //오브젝트(나무, 유리, 돼지) -----> 폭탄



}

// Called every frame
void ARIM_TNT::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Shoot();
	


}


//[폭탄이 터지는 조건]
//1. 새가 폭탄에 닿는다. 무조건 터진다.(없어진다)
//2. 폭탄이 오브젝트(나무, 유리, 폭탄 등)에 닿는다. 일정 충격 이상일 경우 터진다.(없어진다)
//3. 폭탄이 땅에 닿는다. 무조건 터진다(없어진다). ---> 킬존 만들어서 구현

//[폭탄이 터지면 발생하는 일]
//1. blastRange(폭탄 범위) 에서 폭탄에 일정 거리 이하로 위치해 있을 때, 적, 나무, 유리 파괴된다.
//2. blastRange(폭탄 범위) 에서 폭탄에 일정 거리 이상으로 위치해 있을 때, 적, 나무, 유리 충격으로 날아간다.


//폭탄에 범위에 따른 피해. 파괴 또는 충격
void ARIM_TNT::ExplosionDamage()
{
	//충돌 정보
	TArray<FOverlapResult> hitInfos;

	//TNT 위치 ★★★왜 액터 로케이션 안 사용?
	FVector center = meshTNT->GetComponentLocation(); 

	//TNT 폭발 범위(blastRange)
	FCollisionShape blastCollision = FCollisionShape::MakeSphere(blastRange);

	//★★★???
	FCollisionObjectQueryParams objectQuerry;
	//★★★???
	FCollisionQueryParams params; 
	params.AddIgnoredActor(this);
	//★★★???
	objectQuerry.AddObjectTypesToQuery(ECC_WorldDynamic);

	//폭발 범위 그리기
	DrawDebugSphere(GetWorld(), center, blastCollision.GetSphereRadius(), 50, FColor::Cyan, true);

	//Ignore 빼고 blastRange(폭발 범위) 안에 있는 모든 물체를 다 체크 한다
	if (GetWorld()->OverlapMultiByObjectType(hitInfos, center, FQuat::Identity, objectQuerry, FCollisionShape::MakeSphere(blastRange), params))
	{
		//★★★???
		for (FOverlapResult& hit : hitInfos) // [i] = FOverlapResult& hit
		{
			hit.GetActor()->GetActorLocation();
			ARIM_Pig* pigTNT = Cast<ARIM_Pig>(hit.GetActor());
			AKYI_Wood* woodTNT = Cast<AKYI_Wood>(hit.GetActor());
			AKYI_Glass* glassTNT = Cast<AKYI_Glass>(hit.GetActor());

			if (500 > 100) //폭발 범위가 blastRangeDie 이하 일 때, 파괴된다. ★★★수정 필요
			{
				if (pigTNT != nullptr) //돼지
				{
					UE_LOG(LogTemp, Warning, TEXT("Pig ---> TNT ---> Pig Destory !!!!!!!!!!"));
					pigTNT->Destroy();
				}
				else if (woodTNT != nullptr) //나무
				{
					UE_LOG(LogTemp, Warning, TEXT("Wood ---> TNT ---> Wood Destory !!!!!!!!!!"));
					Destroy();
				}
				else if (glassTNT != nullptr) //유리
				{
					UE_LOG(LogTemp, Warning, TEXT("Glass ---> TNT ---> Glass Destory !!!!!!!!!!"));
					Destroy();
				}
			}
			else //폭발 범위가 blastRangeDie 이상 일 때, 충격이 발생한다. ★★★수정 필요
			{
				if (pigTNT != nullptr) //돼지
				{
					UE_LOG(LogTemp, Warning, TEXT("Pig ---> TNT ---> Pig Impulse !!!!!!!!!!"));
					pigTNT->compCollision->AddRadialImpulse(GetActorLocation(), blastRange, ImpulseRange, ERadialImpulseFalloff::RIF_Constant, true);
				}
// 				else if (woodTNT != nullptr) //나무
// 				{
// 					UE_LOG(LogTemp, Warning, TEXT("Wood ---> TNT ---> Wood Impulse !!!!!!!!!!"));
// 					woodTNT->compCollision->AddRadialImpulse(GetActorLocation(), blastRange, ImpulseRange, ERadialImpulseFalloff::RIF_Constant, true);
// 				}
// 				else if (glassTNT != nullptr) //유리
// 				{
// 					UE_LOG(LogTemp, Warning, TEXT("Glass ---> TNT ---> Glass Impulse !!!!!!!!!!"));
// 					glassTNT->compCollision->AddRadialImpulse(GetActorLocation(), blastRange, ImpulseRange, ERadialImpulseFalloff::RIF_Constant, true);
// 				}
			}
		}
	}
}


//조건에 따라 폭탄이 터진다
void ARIM_TNT::Shoot()
{
	if (redBirdAttack == true || yellowBirdAttack == true || blueBirdAttack == true || blackBierdAttack == true) //새가 폭탄에게 닿으면
	{
		UE_LOG(LogTemp, Warning, TEXT("Bird Attack -----> TNT Destroy !!!!!!!!!!"));
		ExplosionDamage();
		Die(); //폭탄이 터진다. 없어진다
	}
	else if (woodAttack == true) //나무가 폭탄에게 닿았을 때
	{
		//if () //나무 collision 의 충격? 속도? 가 OOO 보다 크면
		//{
		UE_LOG(LogTemp, Warning, TEXT("Wood Attack -----> TNT Destroy !!!!!!!!!!"));
		ExplosionDamage();
		Die(); //폭탄이 터진다. 없어진다
		//}
	}
	else if (glassAttack == true) //유리가 폭탄에게 닿았을 때
	{
		//if () //유리(나무보다 약함) collision 의 충격? 속도? 가 OOO 보다 크면
		//{
		UE_LOG(LogTemp, Warning, TEXT("Glass Attack -----> TNT Destroy !!!!!!!!!!"));
		ExplosionDamage();
		Die(); //폭탄이 터진다. 없어진다
		//}
	}
	else if (pigAttack == true) //돼지가 폭탄에게 닿았을 때
	{
		UE_LOG(LogTemp, Warning, TEXT("Pig Attack -----> TNT Destroy !!!!!!!!!!"));
		ExplosionDamage();
		Die(); //폭탄이 터진다. 없어진다
	}
}


//새 -----> 폭탄
void ARIM_TNT::ComponentBeginOverlapBird(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->GetName().Contains(TEXT("red"))) //빨간 새가 폭탄이 닿으면
	{
		AKYI_AngryRed* redOverlap = Cast<AKYI_AngryRed>(OtherActor);
		redBirdAttack = true;

		UE_LOG(LogTemp, Warning, TEXT("Red Bird ---> Overlap ---> TNT !!!!!!!!!!"));
	}
	else if (OtherActor->GetName().Contains(TEXT("yellow"))) //노란 새가 폭탄이 닿으면
	{
		AKYI_AngryChuck* yellowOverlap = Cast<AKYI_AngryChuck>(OtherActor);
		yellowBirdAttack = true;

		UE_LOG(LogTemp, Warning, TEXT("Yellow Bird ---> Overlap ---> TNT !!!!!!!!!!"));
	}
	else if (OtherActor->GetName().Contains(TEXT("blue"))) //파란 새가 폭탄이 닿으면
	{
		ARIM_BirdBlue* blueOverlap = Cast<ARIM_BirdBlue>(OtherActor);
		blueBirdAttack = true;

		UE_LOG(LogTemp, Warning, TEXT("Blue Bird ---> Overlap ---> TNT !!!!!!!!!!"));
	}
	else if (OtherActor->GetName().Contains(TEXT("black"))) //검은 새가 폭탄이 닿으면
	{
		ARIM_BirdBlack* blackOverlap = Cast<ARIM_BirdBlack>(OtherActor);
		blackBierdAttack = true;

		UE_LOG(LogTemp, Warning, TEXT("Black Bird ---> Overlap ---> TNT !!!!!!!!!!"));
	}
}


//오브젝트 -----> 폭탄
void ARIM_TNT::ComponentBeginOverlapObject(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->GetName().Contains(TEXT("Wood"))) //오브젝트 "나무"에 닿으면
	{
		AKYI_Wood* woodOverlap = Cast<AKYI_Wood>(OtherActor);
		woodAttack = true;

		UE_LOG(LogTemp, Warning, TEXT("Wood ---> Overlap ---> TNT !!!!!!!!!!"));
	}
	else if (OtherActor->GetName().Contains(TEXT("Glass"))) //오브젝트 "유리"에 닿으면
	{
		AKYI_Glass* glassOverlap = Cast<AKYI_Glass>(OtherActor);
		glassAttack = true;

		UE_LOG(LogTemp, Warning, TEXT("Glass ---> Overlap ---> TNT !!!!!!!!!!"));
	}
	else if (OtherActor->GetName().Contains(TEXT("Pig"))) //오브젝트 "적"에 닿으면
	{
		ARIM_Pig* pigOverlap = Cast<ARIM_Pig>(OtherActor);
		pigAttack = true;

		UE_LOG(LogTemp, Warning, TEXT("Pig ---> Overlap ---> TNT !!!!!!!!!!"));
	}
}


//폭탄 없어진다
void ARIM_TNT::Die()
{
	UGameplayStatics::PlaySound2D(GetWorld(), explosionSound, 5);
	Destroy();
}