// Fill out your copyright notice in the Description page of Project Settings.


#include "KYI_AngryRed.h"
#include <Components/SkeletalMeshComponent.h>
#include <Engine/SkeletalMesh.h>
#include "GameFramework/ProjectileMovementComponent.h"
#include <Components/SphereComponent.h>


// Sets default values
AKYI_AngryRed::AKYI_AngryRed()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	sphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Collision"));
	SetRootComponent(sphereComp);
	//Skeletal Mesh ¼³Á¤
	skeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	ConstructorHelpers::FObjectFinder<USkeletalMesh> tempMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/Resource/Red/Red.Red'"));
	if (tempMesh.Succeeded())
		skeletalMesh->SetSkeletalMesh(tempMesh.Object);
	skeletalMesh->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
	skeletalMesh->SetupAttachment(sphereComp);
	movement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));
	movement->SetUpdatedComponent(sphereComp);
	movement->InitialSpeed = 1000;
	movement->MaxSpeed = 2000;
	movement->bShouldBounce = true;
	movement->Bounciness = 0.5f;
}

// Called when the game starts or when spawned
void AKYI_AngryRed::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AKYI_AngryRed::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

