// Fill out your copyright notice in the Description page of Project Settings.


#include "KYI_AngryChuck.h"
#include <GameFramework/ProjectileMovementComponent.h>
#include <Components/SkeletalMeshComponent.h>
#include <Components/SphereComponent.h>
#include "RIM_Player.h"

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
	movement->bShouldBounce = true;
	movement->Bounciness = 0.5f;
}

// Called when the game starts or when spawned
void AKYI_AngryChuck::BeginPlay()
{
	Super::BeginPlay();
	SetLifeSpan(4);
	player = Cast<ARIM_Player>(GetOwner());
}

// Called every frame
void AKYI_AngryChuck::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

}

void AKYI_AngryChuck::BirdYellowSkill() {
	
}

