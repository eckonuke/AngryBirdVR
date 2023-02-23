// Fill out your copyright notice in the Description page of Project Settings.


#include "KYI_Wood.h"
#include <Components/BoxComponent.h>
#include <Components/StaticMeshComponent.h>
#include <Kismet/GameplayStatics.h>
#include <Particles/ParticleSystem.h>

// Sets default values
AKYI_Wood::AKYI_Wood()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Comp"));
	SetRootComponent(boxComp);
	boxComp->SetBoxExtent(FVector(50));
	boxComp->SetSimulatePhysics(true);

	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Comp"));
	meshComp->SetupAttachment(boxComp);
	ConstructorHelpers::FObjectFinder<UStaticMesh> tempMesh(TEXT("/Script/Engine.StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	if (tempMesh.Succeeded())
		meshComp->SetStaticMesh(tempMesh.Object);
	meshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	meshComp->SetSimulatePhysics(false);

	//¿Ã∆Â∆Æ
	ConstructorHelpers::FObjectFinder<UParticleSystem> tempEffect(TEXT("/Script/Engine.ParticleSystem'/Game/Realistic_Starter_VFX_Pack_Vol2/Particles/Destruction/P_Destruction_Wood.P_Destruction_Wood'"));
	if (tempEffect.Succeeded()) {
		damageEffect = tempEffect.Object;
	}
}

// Called when the game starts or when spawned
void AKYI_Wood::BeginPlay()
{
	Super::BeginPlay();
	boxComp->OnComponentHit.AddDynamic(this, &AKYI_Wood::ComponentHitObject);
}

// Called every frame
void AKYI_Wood::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AKYI_Wood::ComponentHitObject(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) {
	AActor* actor = Hit.GetActor();
	if (Hit.GetActor()) {
		if (actor->GetVelocity().Length() > 300) {
			FString name = Hit.GetActor()->GetName();
			if (name.Contains("Red") || name.Contains("Yellow") || name.Contains("Black")) {
				Die();
			}
		}
	}
}

void AKYI_Wood::Die() {
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), damageEffect, GetActorLocation());
	Destroy();

}