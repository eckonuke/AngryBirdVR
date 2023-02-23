// Fill out your copyright notice in the Description page of Project Settings.


#include "KYI_AngryChuck.h"
#include <GameFramework/ProjectileMovementComponent.h>
#include <Components/SkeletalMeshComponent.h>
#include <Components/SphereComponent.h>
#include "RIM_Player.h"
#include "KYI_Glass.h"
#include "KYI_Wood.h"
#include "RIM_Pig.h"
#include "RIM_TNT.h"

// Sets default values
AKYI_AngryChuck::AKYI_AngryChuck()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	sphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Collision"));
	SetRootComponent(sphereComp);
	sphereComp->SetSphereRadius(20);
	sphereComp->SetSimulatePhysics(true);
	//Skeletal Mesh ¼³Á¤
	skeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	//skeletalMesh->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
	skeletalMesh->SetupAttachment(sphereComp);
	skeletalMesh->SetRelativeRotation(FRotator(0, -90, 0));
	skeletalMesh->SetRelativeLocation(FVector(0, 0, -10));
	skeletalMesh->SetRelativeScale3D(FVector(0.2));
	movement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));
	movement->SetUpdatedComponent(sphereComp);
}

// Called when the game starts or when spawned
void AKYI_AngryChuck::BeginPlay()
{
	Super::BeginPlay();
	SetLifeSpan(4);
	player = Cast<ARIM_Player>(GetOwner());
	sphereComp->OnComponentBeginOverlap.AddDynamic(this, &AKYI_AngryChuck::ComponentHitObject);
}

// Called every frame
void AKYI_AngryChuck::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

}

void AKYI_AngryChuck::BirdYellowSkill() {
	
}

void AKYI_AngryChuck::ComponentHitObject(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit)
{
	AActor* actor = Hit.GetActor();
	if (actor) {
		AKYI_Glass* glass = Cast<AKYI_Glass>(actor);
		AKYI_Wood* wood = Cast<AKYI_Wood>(actor);
		ARIM_Pig* pig = Cast<ARIM_Pig>(actor);
		ARIM_TNT* tnt = Cast<ARIM_TNT>(actor);
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