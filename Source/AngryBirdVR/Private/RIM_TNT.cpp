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
	//compCollision-> //콜리전
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
	compCollision->OnComponentHit.AddDynamic(this, &ARIM_TNT::ComponentHitObject); //오브젝트(나무, 유리, 돼지) -----> 폭탄
	player = Cast<ARIM_Player>(GetWorld()->GetFirstPlayerController()->GetPawn());
}

// Called every frame
void ARIM_TNT::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
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
	FVector center = GetActorLocation(); 

	//TNT 폭발 범위(blastRange)
	FCollisionShape blastCollision = FCollisionShape::MakeSphere(blastRange);
	FCollisionObjectQueryParams objectQuerry;
	objectQuerry.AddObjectTypesToQuery(ECC_WorldDynamic);
	objectQuerry.AddObjectTypesToQuery(ECC_Destructible);
	FCollisionQueryParams params;
	params.AddIgnoredActor(this);
	//★★★???

	//폭발 범위 그리기
	DrawDebugSphere(GetWorld(), center, blastCollision.GetSphereRadius(), 50, FColor::Cyan, true);

	//Ignore 빼고 blastRange(폭발 범위) 안에 있는 모든 물체를 다 체크 한다
	if (GetWorld()->OverlapMultiByObjectType(hitInfos, center, FQuat::Identity, objectQuerry, FCollisionShape::MakeSphere(blastRange), params))
	{
		//★★★???
		for (FOverlapResult& hit : hitInfos) // [i] = FOverlapResult& hit
		{
			if (hit.GetActor() != nullptr) {
				FString name = hit.GetActor()->GetName();
				if (name.Contains("Angry") || name.Contains("Glass") || name.Contains("Wood") || name.Contains("Pig")) {
					double distance = FVector::Distance(GetActorLocation(), hit.GetActor()->GetActorLocation());
					UE_LOG(LogTemp, Warning, TEXT("%f"), distance);
					if (distance <= blastRangeDie) //폭발 범위가 blastRangeDie 이하 일 때, 파괴된다. ★★★수정 필요
					{
						if (name.Contains("Pig")) {
							player->score += 5000;
						}
						else if (name.Contains("Wood") || name.Contains("Glass")) {
							player->score += 500;
						}
						hit.GetActor()->Destroy();
					}
					else //폭발 범위가 blastRangeDie 이상 일 때, 충격이 발생한다. ★★★수정 필요
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

//오브젝트 -----> 폭탄
void ARIM_TNT::ComponentHitObject(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	FString name = Hit.GetActor()->GetName();
	if (name.Contains("Angry") || name.Contains("Glass") || name.Contains("Wood") || name.Contains("Pig")) {
		UE_LOG(LogTemp, Warning, TEXT("Hit by %s"), *OtherActor->GetName());
		ExplosionDamage();
		Die();
	}
}


//폭탄 없어진다
void ARIM_TNT::Die() {
	UGameplayStatics::PlaySound2D(GetWorld(), explosionSound, 5);
	this->Destroy();
}