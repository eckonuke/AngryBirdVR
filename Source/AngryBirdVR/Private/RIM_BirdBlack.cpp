// Fill out your copyright notice in the Description page of Project Settings.


#include "RIM_BirdBlack.h"
#include <Components/SphereComponent.h>
#include <Components/StaticMeshComponent.h>
#include <GameFramework/ProjectileMovementComponent.h>
#include "DrawDebugHelpers.h"
#include "KYI_AngryRed.h"
#include "KYI_AngryChuck.h"
#include "RIM_BirdBlue.h"
#include "RIM_BirdBlack.h"
#include "KYI_Wood.h"
#include "KYI_Glass.h"
#include "RIM_Pig.h"
#include <Components/SkeletalMeshComponent.h>
#include <Components/BoxComponent.h>
#include "RIM_Player.h"
#include "RIM_TNT.h"
#include <Particles/ParticleSystem.h>
#include <Kismet/GameplayStatics.h>
#include <Sound/SoundBase.h>

// Sets default values
ARIM_BirdBlack::ARIM_BirdBlack()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//충돌체
	compCollision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	RootComponent = compCollision; //루트컴포넌트로 세팅. compCollision->SetupAttachment(RootComponent);
	compCollision->SetCollisionProfileName(TEXT("BlockAll"));
	compCollision->SetSphereRadius(60); //▶충돌체 크기. 추후 수정
	compCollision->SetSimulatePhysics(true);

	//외관
	meshBlack = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("BlackBird"));
	meshBlack->SetupAttachment(compCollision);
// 	ConstructorHelpers::FObjectFinder<UStaticMesh> tempBird(TEXT("/Script/Engine.StaticMesh'/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere'")); //▶추후 수정
// 	if (tempBird.Succeeded())
// 	{
// 		meshBlack->SetStaticMesh(tempBird.Object);
// 	}
	meshBlack->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	//meshBlue->SetRelativeLocation(FVector(0, 0, 0)); //▶추후 수정
	meshBlack->SetRelativeScale3D(FVector(0.8f)); //▶추후 수정
	meshBlack->SetRelativeLocation(FVector(-6, 1, -54));
	meshBlack->SetRelativeRotation(FRotator(0, 90, 0));

	//발사체 ★★★영상에 의하면 필요없으나 일단 넣음
	compMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movement"));
	compMovement->SetUpdatedComponent(compCollision);
	compMovement->InitialSpeed = 0; //초기속도. ▶필요시 추후 수정
	compMovement->MaxSpeed = 0; //최대속도. ▶필요시 추후 수정
	compMovement->bShouldBounce = true; //반동여부. 튕기는 여부
	compMovement->Bounciness = 0.5f; //얼마나 잘 튕기에 할 것인가. 반동. 탄성. ▶필요시 추후 수정
	//InitialLifeSpan = 10.0f; //생명 시간. ▶필요시 추후 수정

	//이펙트
	ConstructorHelpers::FObjectFinder<UParticleSystem> tempEffect(TEXT("/Script/Engine.ParticleSystem'/Game/Realistic_Starter_VFX_Pack_Vol2/Particles/Explosion/P_Explosion_Big_A.P_Explosion_Big_A'"));
	if (tempEffect.Succeeded()) {
		explodeEffect = tempEffect.Object;
	}
	ConstructorHelpers::FObjectFinder<USoundBase> tempSound(TEXT("/Script/Engine.SoundWave'/Game/Resource/Sound/TNTExplosionSound.TNTExplosionSound'"));
	if (tempSound.Succeeded()) {
		explosionSound = tempSound.Object;
	}
}

// Called when the game starts or when spawned
void ARIM_BirdBlack::BeginPlay()
{
	Super::BeginPlay();
	player = Cast<ARIM_Player>(GetWorld()->GetFirstPlayerController()->GetPawn());
	compCollision->OnComponentHit.AddDynamic(this, &ARIM_BirdBlack::ComponentHitObject);
	SetLifeSpan(4);
}

// Called every frame
void ARIM_BirdBlack::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARIM_BirdBlack::ComponentHitObject(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	AActor* actor = Hit.GetActor();
	if (actor) {
		glass = Cast<AKYI_Glass>(actor);
		wood = Cast<AKYI_Wood>(actor);
		pig = Cast<ARIM_Pig>(actor);
		tnt = Cast<ARIM_TNT>(actor);
		if (glass) {
			glass->Die();
		}
		else if (wood) {
			wood->Die();
		}
		else if (pig) {
			pig->Die();
		}
		else if (tnt) {
			tnt->Die();
		}
	}
}


//새 폭발 범위에 따른 피해. 파괴 또는 충격
void ARIM_BirdBlack::ExplosionDamage()
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
				if (name.Contains("Angry") || name.Contains("Glass") || name.Contains("Wood") || name.Contains("Pig") || name.Contains("TNT")) {
					double distance = FVector::Distance(GetActorLocation(), hit.GetActor()->GetActorLocation());
					tnt = Cast<ARIM_TNT>(hit.GetActor());
					if (distance <= blastRangeDie) //폭발 범위가 blastRangeDie 이하 일 때, 파괴된다. ★★★수정 필요
					{
						if (name.Contains("Pig")) {
							player->score += 5000;
						}
						else if (name.Contains("Wood") || name.Contains("Glass")) {
							player->score += 500;
						}
						else if (tnt) {
							tnt->ExplosionDamage();
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
						else if (tnt) {
							tnt->ExplosionDamage();
						}
					}
				}
			}
		}
	}
	//폭발 이펙트
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), explodeEffect, GetActorLocation());
	UGameplayStatics::PlaySound2D(GetWorld(), explosionSound, 5);
}